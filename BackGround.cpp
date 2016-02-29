/* ============================================================
	・BackGround.cpp
			背景クラスの処理
============================================================= */

#include "stdafx.h"

#include "BackGround.h"
#include "DxGraphic.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		コンストラクタ
------------------------------------------ */
CBackGround::CBackGround() 
	: m_pVertex( NULL ),
	  m_pTexture( NULL )
{
}

CBackGround::CBackGround(LPDIRECT3DTEXTURE9 tex)
	: m_pVertex( NULL ),
	  m_pTexture( NULL )
{
	InitBackGround( tex );
}

/* -----------------------------------------
		デストラクタ
------------------------------------------ */
CBackGround::~CBackGround() {
	CleanUp();	// 解放処理呼び出し
}

/* -----------------------------------------
	InitBackGround() : 初期化関数
------------------------------------------ */
void CBackGround::InitBackGround(LPDIRECT3DTEXTURE9 tex) {

	// デフォルト頂点データ(背景用)
	CUSTOMVERTEX defaultBGVertices[4] = {
		{   0.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
		{ 640.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
		{ 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f },
		{	0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f } 
	};


	// 頂点データメンバ変数にデフォルト値を代入
	for(int i = 0; i < 4; i++) {
		m_Vertices[i] = DefaultBGVertices[i];
	}

	// テクスチャメンバ設定
	m_pTexture = tex;

	// 頂点バッファの作成
	if(FAILED(CDxGraphic::m_pD3DDevice->CreateVertexBuffer( sizeof(CUSTOMVERTEX)*4, 0, FVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &m_pVertex, NULL ))) {
		MessageBox(NULL, _T("頂点バッファの作成に失敗しました"), _T("Error"), MB_OK | MB_ICONSTOP);
	}

	// 頂点バッファをロックし頂点データをコピーする
	void *pData;
	if(SUCCEEDED(m_pVertex->Lock(0, sizeof(CUSTOMVERTEX)*4, (void**)&pData, 0))) {
		memcpy(pData, m_Vertices, sizeof(CUSTOMVERTEX)*4);
		m_pVertex->Unlock();			// ロックを解除
	}
}

/* ------------------------------------------
	CleanUp() : 解放処理
------------------------------------------- */
void CBackGround::CleanUp() {
	SAFE_RELEASE( m_pVertex );	// 頂点バッファを解放
	m_pVertex = NULL;
}

/* -----------------------------------------------------------------------
	ScrollBackGround() : 頂点データを変えて背景をスクロールさせる関数
		スクロールにはラップテクスチャアドレッシングモードを利用し、
		毎フレームごとにテクスチャ座標をずらしていく。
			第一引数: u軸の移動量
			第二引数: v軸の移動量
----------------------------------------------------------------------- */
void CBackGround::ScrollBackGround(float moveU, float moveV) {

	// もし各頂点のu座標がデフォルト頂点座標から4.0f離れたら頂点をデフォルト頂点座標に戻す
	if(	abs(DefaultBGVertices[0].tu - m_Vertices[0].tu) >= 4.0f
		&& abs(DefaultBGVertices[1].tu - m_Vertices[1].tu) >= 4.0f
		&& abs(DefaultBGVertices[2].tu - m_Vertices[2].tu) >= 4.0f
		&& abs(DefaultBGVertices[3].tu - m_Vertices[3].tu) >= 4.0f )
	{
		for(int i = 0; i < 4; i++) {
			m_Vertices[i].tu = DefaultBGVertices[i].tu;
		}
	}

	// もし各頂点のv座標がデフォルト頂点座標から4.0f離れたら頂点をデフォルト頂点座標に戻す
	if(	abs(DefaultBGVertices[0].tu - m_Vertices[0].tu) >= 4.0f
		&& abs(DefaultBGVertices[1].tv - m_Vertices[1].tv) >= 4.0f
		&& abs(DefaultBGVertices[2].tv - m_Vertices[2].tv) >= 4.0f
		&& abs(DefaultBGVertices[3].tv - m_Vertices[3].tv) >= 4.0f )
	{
		for(int i = 0; i < 4; i++) {
			m_Vertices[i].tv = DefaultBGVertices[i].tv;
		}
	}

	for(int i = 0; i < 4; i++) {
		m_Vertices[i].tu += moveU;	// 各頂点をu軸方向に移動
		m_Vertices[i].tv += moveV;	// 各頂点をv軸方向に移動
	}

	void *pData;
	if(SUCCEEDED(m_pVertex->Lock(0, sizeof(CUSTOMVERTEX)*4, (void**)&pData, 0))) {
		memcpy(pData, m_Vertices, sizeof(CUSTOMVERTEX)*4);
		m_pVertex->Unlock();			// ロックを解除
	}
}


/* -----------------------------------------
	Draw() : 描画関数
------------------------------------------- */
void CBackGround::Draw() {
	LPDIRECT3DDEVICE9 D3DDevice = CDxGraphic::m_pD3DDevice;
	D3DDevice->SetStreamSource(0, m_pVertex, 0, sizeof(CUSTOMVERTEX) );
	D3DDevice->SetTexture(0, m_pTexture);
	D3DDevice->SetFVF( FVF_CUSTOMVERTEX );
	D3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}