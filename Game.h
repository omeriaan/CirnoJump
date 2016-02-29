/* ====================================
	・Game.h
		ゲーム処理クラス
===================================== */

#ifndef __GAME_H__
#define __GAME_H__

/* ----- プロトタイプ宣言 ----- */
class CScene;
class CSceneTitle;
class CSceneGameMain;

enum Scene;			// シーンの種類はscene.hに記述

/* ----- Gameクラス ----- */
class CGame {
private:
	static CScene*			m_pScene;			// Sceneオブジェクト

	static CSceneTitle*		m_pSceneTitle;		// タイトルシーンクラス
	static CSceneGameMain*	m_pSceneGameMain;	// ゲームメインシーンクラス

public:
	CGame();							// コンストラクタ
	~CGame();							// デストラクタ
	void CleanUp();						// オブジェクト解放関数
	void UpDate();						// ゲームシーンを更新し、シーンを実行する関数
	static void ChangeScene(Scene);		// ゲームシーンを切り替える関数
};

#endif