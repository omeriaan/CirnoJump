/* ============================================================
	・Scene_Title.cpp
			ゲームタイトル画面の処理
============================================================= */

#include "stdafx.h"

#include "WinMain.h"
#include "Game.h"
#include "Scene_Title.h"
#include "DxGraphic.h"
#include "DIKeyBoard.h"
#include "TextureManager.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

/* -----------------------------------------
		コンストラクタ
------------------------------------------ */
CSceneTitle::CSceneTitle() {
	Init();
}

/* -----------------------------------------
		デストラクタ
------------------------------------------ */
CSceneTitle::~CSceneTitle() {
	CleanUp();
}

/* -----------------------------------------
	・Init() : 初期化関数
------------------------------------------ */
void CSceneTitle::Init() {
	// カーソルの初期位置
	m_Cursor.x = 59;
	m_Cursor.y = 294;

	m_isPrsLast = false;	
	m_nowSelect = Start;	// 「すたーと」パネルにあわせる
}

/* -----------------------------------------
	・CleanUp() : 解放処理関数
------------------------------------------ */
void CSceneTitle::CleanUp() {
}

/* -----------------------------------------
	・Exec() : 実行関数
------------------------------------------ */
void CSceneTitle::Exec() {
	MoveCursor();	// カーソル移動処理

	// もしエンターが押されたらシーンを変更
	if(CDIKeyBoard::GetKeyPrs( DIK_RETURN )) {
		switch( m_nowSelect ) {
			case Start:
				CGame::ChangeScene( Scene_GAMEMAIN );
				break;
			
			case Option:
				break;

			case End:
				PostMessage(GethWnd(), WM_QUIT, 0, 0);	// メインループを抜けて終了
				break;
		}
		//return;
	}

	Draw();			// 描画処理
}

/* -----------------------------------------
	・MoveCursor() : カーソル移動処理関数
------------------------------------------ */
void CSceneTitle::MoveCursor() { 
	// 各パネルのy座標
	//「すたーと」パネル	: y = 294
	//「おぷしょん」パネル	: y = 344
	//「おわる」パネル		: y = 394

	if(CDIKeyBoard::GetKeyPrs( DIK_UP ) && !m_isPrsLast) {
		switch( m_nowSelect ) {
			case Start:
				m_nowSelect = End;
				m_Cursor.y = 394;
				break;

			case Option:
				m_nowSelect = Start;
				m_Cursor.y = 294;
				break;

			case End:
				m_nowSelect = Option;
				m_Cursor.y =344;
				break;
		}
	}
	else if(CDIKeyBoard::GetKeyPrs( DIK_DOWN ) && !m_isPrsLast) {
		switch( m_nowSelect ) {
			case Start:
				m_nowSelect = Option;
				m_Cursor.y = 344;
				break;

			case Option:
				m_nowSelect = End;
				m_Cursor.y = 394;
				break;

			case End:
				m_nowSelect = Start;
				m_Cursor.y = 294;
				break;
		}
	}

	if(CDIKeyBoard::GetKeyPrs( DIK_UP ) || CDIKeyBoard::GetKeyPrs( DIK_DOWN )) {
		m_isPrsLast = true;
	}
	else {
		m_isPrsLast = false;
	}
}

/* -------------------------------------------
	・Draw() :　描画処理処理関数
		描画はスプライトを使用
-------------------------------------------- */
void CSceneTitle::Draw() {
	/* ----- 各表示矩形を設定 ----- */
	RECT	bg_rc		= {0, 0, 640, 480},
			logo_rc		= {0, 0, 360, 240},
			cirno_rc	= {0, 0, 424, 424},
			start_rc	= {0, 0, 136, 48},
			option_rc	= {0, 0, 136, 48},
			end_rc		= {0, 0, 136, 48},
			cursor_rc	= {0, 0, 64, 64};

	/* ----- 各表示位置を設定 ----- */
	D3DXVECTOR3 center(0, 0, 0); 
	D3DXVECTOR3 bg_pos(0, 0, 0),
				logo_pos(10, 50, 0),
				cirno_pos(216, 56, 0),
				start_pos(107, 294, 0),
				option_pos(107, 344, 0),
				end_pos(107, 394, 0),
				cursor_pos((float)m_Cursor.x, (float)m_Cursor.y, 0);		

	CDxGraphic::m_pD3DXSprite->Begin( D3DXSPRITE_ALPHABLEND );
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_BG.png")), &bg_rc, &center, &bg_pos, 0xFFFFFFFF );				// タイトル背景
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_Cirno.dds")), &cirno_rc, &center, &cirno_pos, 0xFFFFFFFF );		// チルノ
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_Logo.dds")), &logo_rc, &center, &logo_pos, 0xFFFFFFFF );			// タイトルロゴ
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_StartPanel.dds")), &start_rc, &center, &start_pos, 0xFFFFFFFF );		// すたーとパネル
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_OptionPanel.dds")), &option_rc, &center, &option_pos, 0xFFFFFFFF );	// おぷしょんパネル
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_EndPanel.dds")), &end_rc, &center, &end_pos, 0xFFFFFFFF );				// おわるパネル
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Snow_S.dds")), &cursor_rc, &center, &cursor_pos, 0xFFFFFFFF );			// 雪カーソル

	CDxGraphic::m_pD3DXSprite->End();
}

