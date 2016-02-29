/* ==========================================================
	・TextureManager.h
			テクスチャ管理クラス
============================================================= */

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "stdafx.h"
#include <d3dx9.h>		// Direct3D & D3DX

/* ---------------------------------------------------
	テクスチャ管理クラス : CTextureManagerクラス
--------------------------------------------------- */
class CTextureManager {
private:
	static BYTE* m_pPointer;								// メモリマップドファイルポインタ
	static map<tstring, LPDIRECT3DTEXTURE9> m_MapTexture;	// テクスチャ管理map

public:
	static bool CreateTexture();						// テクスチャ作成関数
	static void DeleteTexture();						// テクスチャ削除関数
	static LPDIRECT3DTEXTURE9 GetTexture(tstring);		// テクスチャgetter
};


#endif