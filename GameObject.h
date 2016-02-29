/* ============================================================
	・GameObject.h
			ゲームオブジェクトのスーパークラス
============================================================= */

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CGameObject {
protected:
	CHARACTER	m_Chara;		// キャラクター座標位置位置
	RECT		m_rectSize;		// 矩形サイズ
	RECT		m_rect;			// 表示するテクスチャ矩形
	D3DXVECTOR3 m_center;		// 矩形の中心座標
	tstring		m_textureName;	// 表示するテクスチャ名
	RECT		m_hitRect;		// 当たり判定矩形
		
public:
	CGameObject() {};		// コンストラクタ	
	~CGameObject() {};		// デストラクタ

	void Draw();			// 描画関数
};

#endif