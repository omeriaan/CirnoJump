/* ============================================================
	・BackGround.h
			背景クラス
============================================================= */

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <d3dx9.h>
struct CUSTOMVERTEX;

class CBackGround {
private:
	IDirect3DVertexBuffer9* m_pVertex;		// 頂点バッファ	
	CUSTOMVERTEX			m_Vertices[4];	// 頂点データ構造体
	LPDIRECT3DTEXTURE9		m_pTexture;		// 背景テクスチャ

public:
	CBackGround();								// コンストラクタ
	CBackGround( LPDIRECT3DTEXTURE9 );			// コンストラクタ(引数あり)
	~CBackGround();								// デストラクタ
	void InitBackGround( LPDIRECT3DTEXTURE9 );	// 初期化関数
	void CleanUp();								// 解放処理
	void ScrollBackGround(float, float);		// 背景スクロール関数
	void Draw();								// 描画関数
};

#endif