/* ============================================================
	・Utsuho.cpp
			お空の処理
============================================================= */
#include "stdafx.h"

#include "DxGraphic.h"
#include "TextureManager.h"
#include "Utsuho.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		コンストラクタ
------------------------------------------ */
CUtsuho::CUtsuho() 
{	
	Init();	// 初期化処理
}

/* -----------------------------------------
		デストラクタ
------------------------------------------ */
CUtsuho::~CUtsuho() {
}

/* -----------------------------------------
	・Init() :　初期化関数
------------------------------------------ */
void CUtsuho::Init() {
	
	/* ----- お空の初期設定 ----- */
	m_Chara.x = 552;		// 初期x座標位置				
	m_Chara.y = 350;		// 初期y座標位置

	m_AnimeCount = 0;		// アニメーションカウント初期化
	m_lastAnime = 0;		// 前フレームのアニメの状態

	m_textureName = _T("img\\Utsuho.dds");	// テクスチャ名

	/* ----- Draw設定 ----- */
	RECT rc = {0, 0, 176, 176};
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
	・Anime() :　アニメーション処理関数
-------------------------------------------- */
void CUtsuho::Anime() {
	int frameSpeed = 10;	// アニメのスピード(フレーム数)

	int i = m_AnimeCount / frameSpeed;

	if(m_lastAnime != i) {
		switch( i ) {
			case 0:
				m_rect.left = 0;
				m_rect.right = 176;
				break;

			case 1:
				m_rect.left = 176;
				m_rect.right = 352;
				break;
		}
		m_lastAnime = i;
	}

	m_AnimeCount++;
	if(m_AnimeCount == frameSpeed * 2) {
		m_AnimeCount = 0;	
	}
}
