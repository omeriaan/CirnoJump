/* ============================================================
	・Cirno.cpp
			チルノの処理
============================================================= */
#include "stdafx.h"

#include "DxGraphic.h"
#include "DIKeyBoard.h"
#include "TextureManager.h"
#include "Cirno.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		コンストラクタ
------------------------------------------ */
CCirno::CCirno() 
{	
	Init();	// 初期化処理
}

/* -----------------------------------------
		デストラクタ
------------------------------------------ */
CCirno::~CCirno() {
}

/* -----------------------------------------
	・Init() :　初期化関数
------------------------------------------ */
void CCirno::Init() {
	
	/* ----- チルノの初期設定 ----- */
	m_Chara.x = 64;			// 初期x座標位置				
	m_Chara.y = 374;		// 初期y座標位置
	m_State = Cirno_Run;	// 走り状態

	m_Vy = 0.0f;			// 移動速度(y軸)
	m_AnimeCount = 0;		// アニメーションカウント初期化
	m_lastAnime = 0;		// 前フレームのアニメの状態

	m_textureName = _T("img\\Cirno.dds");	// テクスチャ名

	/* ----- Draw設定 ----- */
	RECT rc = {0, 0, 128, 128};
	m_rectSize = rc;	// 矩形サイズ
	m_rect = rc;		// 初期表示矩形 {left, top, right, bottom : 0, 0, 128, 128}

	// 初期当たり判定
	m_hitRect.top = m_Chara.y - 50;
	m_hitRect.left = m_Chara.x - 20;
	m_hitRect.bottom = m_Chara.y + 45;
	m_hitRect.right = m_Chara.x + 30;

	// 矩形の中心座標
	m_center.x = (float)rc.right/2;
	m_center.y = (float)rc.bottom/2;
	m_center.z = 0;

}

/* -------------------------------------------
	・Jump() :　ジャンプアクション処理関数
-------------------------------------------- */
void CCirno::Jump() {
	int defaultY = 374;		// チルノ初期位置:y軸374

	// チルノのジャンプの高さ、落下速度の調整 
	float jump_speed = 7.0f;	// ジャンプの初速度
	float jump_accel = -0.15f;	// ジャンプの加速度


	// 走り状態の時
	if(m_State == Cirno_Run) {
		// スペースキーが押されたら
		if(CDIKeyBoard::GetKeyPrs( DIK_SPACE )) {
			m_State = Cirno_JumpUp;	// 状態をジャンプ中にする
			m_Vy = jump_speed;			// 初速でジャンプ
		}
	}
	// ジャンプ状態の時
	else {
		m_Vy += jump_accel;		// フレーム毎に速度に加速度を加えていく

		// 可変長ジャンプ処理
		// 上昇中にボタンを放したら下降に移行
		if((m_Vy > 0) && !CDIKeyBoard::GetKeyPrs( DIK_SPACE )) {
			m_Vy = 0.0f;
		}

		// 速度が負ならチルノの状態を下降中にする
		if(m_Vy < 0) {
			m_State = Cirno_JumpDown;
		}

		// 初期位置より下に行かないようにする
		if(m_Chara.y >= defaultY) {
			m_Chara.y = defaultY;
			m_Vy = 0.0f;
			m_State = Cirno_Run;
		}
	}
	
	m_Chara.y -= (int)m_Vy;			// チルノの位置を更新

	// 当たり判定更新
	m_hitRect.top = m_Chara.y - 50;
	m_hitRect.bottom = m_Chara.y + 45;

}

/* -------------------------------------------
	・Anime() :　アニメーション処理関数
-------------------------------------------- */
void CCirno::Anime() {
	int frameSpeed = 10;	// 走り状態のチルノアニメのスピード(フレーム数)

	switch(m_State) {

		/* ----- 走り状態の時 ----- */
		case Cirno_Run:
			{
				/* ----- frameSpeed毎に表示矩形を変える ----- */
				int i = m_AnimeCount / frameSpeed;

				if(m_lastAnime != i) {
					switch( i ) {
						case 0:
							m_rect.left = 0;
							m_rect.right = 128;
							break;
		
						case 1:
							m_rect.left = 128;
							m_rect.right = 256;
							break;

						case 2:
							m_rect.left = 256;
							m_rect.right = 384;
							break;

						case 3:
							m_rect.left = 384;
							m_rect.right = 512;
							break;
					}
					m_lastAnime = i;
				}
			}		
			m_AnimeCount++;
			if(m_AnimeCount == frameSpeed * 4) {
				m_AnimeCount = 0;
			}
			break;

		/* ----- ジャンプ中（上昇）の時 ---- */
		case Cirno_JumpUp:
			m_rect.left = 512;
			m_rect.right = 640;
			break;

		/* ----- ジャンプ中（下降）の時 ---- */
		case Cirno_JumpDown:
			m_rect.left = 640;
			m_rect.right = 768;
			break;
	}
}
