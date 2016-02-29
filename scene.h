/* ===============================================================
	・scene.h
		ゲーム遷移関連のインターフェイスクラス(抽象クラス)
		& Sceneゲッター関数
================================================================ */

#ifndef __SCENE_H__
#define __SCENE_H__

// ゲームシーンの種類
enum Scene { 
	Scene_TITLE,
	Scene_GAMEMAIN 
};

class CScene {
public:	
	virtual	~CScene() {}			// 仮想デストラクタ
	virtual void Exec() = 0;		// 実行関数 :純粋仮想関数(必ずオーバーライドされる関数 : 抽象メソッド)
	virtual	void Init() = 0;		// 初期化関数
	virtual void CleanUp() = 0;		// 解放処理関数
};

#endif