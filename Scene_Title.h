/* =====================================
		・Scene_Title.h
			ゲームタイトル画面クラス
====================================== */

#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "scene.h"

// 選択の種類
enum Select {
	Start,		// 「すたーと」
	Option,		// 「おぷしょん」
	End			// 「おわる」
};

class CSceneTitle : public CScene {
private :
	CHARACTER	m_Cursor;		// カーソルの位置
	Select		m_nowSelect;	// 現在の選択
	bool		m_isPrsLast;	// 前フレームに押したフラグ
	
public:
	CSceneTitle();		// コンストラクタ			
	~CSceneTitle();		// デストラクタ
	void Exec();		// 実行関数
	void MoveCursor();	// カーソル移動処理関数
	void Init();		// 初期化関数
	void CleanUp();		// 解放処理関数
	void Draw();		// 描画関数
};

#endif