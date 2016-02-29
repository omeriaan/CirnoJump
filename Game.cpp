/* ==========================================================
	・Game.cpp
			ゲーム内容の処理
============================================================= */

#include "stdafx.h"

#include "Game.h"
#include "scene.h"
#include "Scene_Title.h"
#include "Scene_GameMain.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

// 静的メンバの初期化
CScene*			CGame::m_pScene			= NULL;
CSceneTitle*	CGame::m_pSceneTitle	= NULL;
CSceneGameMain*	CGame::m_pSceneGameMain = NULL;


/* -----------------------------------------
		コンストラクタ
------------------------------------------ */
CGame::CGame() {
	m_pSceneTitle = new CSceneTitle();
	m_pSceneGameMain = new CSceneGameMain();
	ChangeScene( Scene_TITLE );
}


/* -----------------------------------------
		デストラクタ
------------------------------------------ */
CGame::~CGame() {
	CleanUp();	// オブジェクトを解放
}

/* -----------------------------------------------
	・CleanUp()		Sceneオブジェクトの解放処理
------------------------------------------------ */
void CGame::CleanUp() {
	delete m_pSceneTitle;
	m_pSceneTitle = NULL;
	delete m_pSceneGameMain;
	m_pSceneGameMain = NULL;
}

/* --------------------------------------------------
	・UpDate()
		シーンの実行
-------------------------------------------------- */
void CGame::UpDate() {
	m_pScene->Exec();			// 現在のシーンを実行
}

/* --------------------------------------------------
	・ChangeScene()
	ゲームシーンを切り替える関数
-------------------------------------------------- */
void CGame::ChangeScene(Scene scene) {
	// m_pSceneがNULLではない場合、前のシーンを掃除する
	if(m_pScene != NULL) {
		m_pScene->CleanUp();
	}

	switch( scene ) {
		case Scene_TITLE:
			m_pScene =  m_pSceneTitle;
			break;

		case Scene_GAMEMAIN:
			m_pScene = m_pSceneGameMain;
			break;
	}

	m_pScene->Init();	// 初期化
}
