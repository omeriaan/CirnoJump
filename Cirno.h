/* ====================================
		・Cirno.h
			チルノクラス
===================================== */

#ifndef __CIRNO_H__
#define __CIRNO_H__

#include <d3dx9.h>
#include "GameObject.h"

// チルノの状態の種類
enum CirnoState {
	Cirno_Run,				// 走っている
	Cirno_JumpUp,			// ジャンプ中（上昇）
	Cirno_JumpDown			// ジャンプ中（下降）
};

class CCirno : public CGameObject{
private:
	CirnoState  m_State;			// 現在のチルノの状態
	int			m_AnimeCount;		// アニメーションカウンタ
	int			m_lastAnime;		// 前フレームのアニメの状態
	float		m_Vy;				// チルノの移動速度(y軸上)

public:
	CCirno();		// コンストラクタ
	~CCirno();		// デストラクタ	
	void Init();	// 初期化関数
	void Jump();	// ジャンプアクション関数
	void Anime();	// アニメーション処理関数
};

#endif