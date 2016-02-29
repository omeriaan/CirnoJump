/* ===================================
		・Scene_GameMain.h
			ゲームメインクラス
==================================== */

#ifndef __SCENE_GAMEMAIN_H__
#define __SCENE_GAMEMAIN_H__

#include "scene.h"
#include <d3dx9.h>
class CBackGround;
class CCirno;
class CUtsuho;

class CSceneGameMain : public CScene {
private:
	// 背景クラス
	CBackGround*	m_pBG_Mountain1;
	CBackGround*	m_pBG_Mountain2;
	CBackGround*	m_pBG_Sky;
	CBackGround*	m_pBG_Clouds;
	CBackGround*	m_pBG_Ground;

	CCirno*	m_pCirno;	// チルノ
	CUtsuho* m_pUtsuho;	// お空


public:
	CSceneGameMain();		// コンストラクタ
	~CSceneGameMain();		// デストラクタ
	void Init();			// 初期化関数
	void Exec();			// 実行関数
	void CleanUp();			// 解放処理関数
};

#endif