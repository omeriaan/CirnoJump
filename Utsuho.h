/* ====================================
		・Utsuho.h
			お空クラス
===================================== */

#ifndef __UTSUHO_H__
#define __UTSUHO_H__

#include <d3dx9.h>
#include "GameObject.h"

class CUtsuho : public CGameObject{
private:
	int			m_AnimeCount;		// アニメーションカウンタ
	int			m_lastAnime;		// 前フレームのアニメの状態
	float		m_Vy;				// チルノの移動速度(y軸上)

public:
	CUtsuho();		// コンストラクタ
	~CUtsuho();		// デストラクタ	
	void Init();	// 初期化関数
	void Anime();	// アニメーション処理関数
};

#endif