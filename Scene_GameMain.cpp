/* ============================================================
	・Scene_GameMain.cpp
			ゲームメインの処理
============================================================= */

#include "stdafx.h"

#include "Scene_GameMain.h"
#include "Game.h"
#include "DxGraphic.h"
#include "DIKeyBoard.h"
#include "BackGround.h"
#include "Cirno.h"
#include "Utsuho.h"
#include "TextureManager.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		コンストラクタ
------------------------------------------ */
CSceneGameMain::CSceneGameMain() 
	: m_pBG_Mountain1( NULL ),
	  m_pBG_Mountain2( NULL ),
	  m_pBG_Sky( NULL ),
	  m_pBG_Clouds( NULL ),
	  m_pBG_Ground( NULL ),
	  m_pCirno( NULL ),
	  m_pUtsuho( NULL )
	{
	}


/* -----------------------------------------
		デストラクタ
------------------------------------------ */
CSceneGameMain::~CSceneGameMain() {
	CleanUp();
}

/* -----------------------------------------
	・Init() :　初期化関数
------------------------------------------ */
void CSceneGameMain::Init() {
	// 背景クラスのインスタンス化

	m_pBG_Mountain1 = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Mountain1.dds") ));
	m_pBG_Mountain2 = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Mountain2.dds") ));
	m_pBG_Sky = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Sky.png") ));
	m_pBG_Clouds = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Clouds.dds") ));
	m_pBG_Ground = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Ground.dds") ));	

	m_pCirno = new CCirno();	// チルノのインスタンス化
	m_pUtsuho = new CUtsuho();	// お空のインスタンス化
}

/* -----------------------------------------
	・CleanUp() : 解放処理関数
------------------------------------------ */
void CSceneGameMain::CleanUp() {

	// 背景クラスのインスタンスを解放
	delete m_pBG_Mountain1;
	delete m_pBG_Mountain2;
	delete m_pBG_Sky;
	delete m_pBG_Clouds;
	delete m_pBG_Ground;
	m_pBG_Mountain1 = NULL;
	m_pBG_Mountain2 = NULL;
	m_pBG_Sky		= NULL;
	m_pBG_Clouds	= NULL;
	m_pBG_Ground	= NULL;

	// インスタンスを解放
	delete m_pCirno;
	m_pCirno = NULL;
	delete m_pUtsuho;
	m_pUtsuho = NULL;
}

/* -----------------------------------------
	・Exec() : 実行関数
------------------------------------------ */
void CSceneGameMain::Exec() {
	// ESCキーを押したらタイトルに戻る
	if(CDIKeyBoard::GetKeyPrs( DIK_ESCAPE )) {
		CGame::ChangeScene( Scene_TITLE );
		return;
	}

	/* ----- 背景の処理 ----- */
	// 背景をスクロール
	m_pBG_Clouds->ScrollBackGround(0.0006f, 0.0f);		// 雲（ゆっくぅ～り動く）
	m_pBG_Mountain1->ScrollBackGround(0.001f, 0.0f);	// 手前の山（ちょい早く動く）
	m_pBG_Mountain2->ScrollBackGround(0.0007f, 0.0f);	// 奥の山（ゆっくり動く）
	m_pBG_Ground->ScrollBackGround(0.003f, 0.0f);		// 地面（早く動く）

	// 背景を描画
	m_pBG_Sky->Draw();			// 空
	m_pBG_Mountain2->Draw();	// 山（奥）
	m_pBG_Mountain1->Draw();	// 山（手前）
	m_pBG_Clouds->Draw();		// 雲
	m_pBG_Ground->Draw();		// 地面


	/* ----- チルノの処理 ----- */
	m_pCirno->Jump();	// チルノジャンプ処理
	m_pCirno->Anime();	// チルノアニメ処理
	m_pCirno->Draw();	// チルノを描画

	/* ----- お空の処理 ----- */
	m_pUtsuho->Anime();	// アニメ処理
	m_pUtsuho->Draw();	// 描画
}
