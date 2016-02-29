/* ===============================================================
	・define_game.h
		このゲームに関するマクロ、定数をまとめたヘッダファイル
================================================================ */

#ifndef __DEFINE_GAME_H__
#define __DEFINE_GAME_H__

#include <d3d9.h>

/* ----- 定数 ----- */
#define		NAME				 _T("GameWin")		// ウィンドウクラス用文字列（ウィンドウ名）
#define		TITLE				 _T("ちるじゃん")	// ウィンドウクラス用文字列（ウィンドウのタイトル）
#define		SIZEWINDOW_WIDTH	 640				// ウィンドウモードの解像度（幅）
#define		SIZEWINDOW_HEIGHT	 480				// ウィンドウモードの解像度（高さ）
#define		SIZEFULL_WIDTH		 640				// フルスクリーンモードの解像度（幅）
#define		SIZEFULL_HEIGHT		 480				// フルスクリーンモードの解像度（高さ)
#define		DATAFILE			_T("cirjum.dat")	// datファイル名

/* ----- FPSControl ----- */
const int	REQUEST_FPS	= 60;						// FPS理想値
const bool	IS_FRAMESKIP = false;					// フレームスキップの有無(true:有 false:無)

/* ----- 2次元頂点構造体 ----- */
struct CUSTOMVERTEX {
	float x, y, z;			// 頂点座標
	float rhw;				// 除算式、 通常は1.0f
	DWORD dwColor;			// 頂点の色
	float tu, tv;			// テクスチャ座標
};
#define FVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/* ----- デフォルト頂点データ(背景用) ----- */
const CUSTOMVERTEX DefaultBGVertices[4] = {
	{   0.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
	{ 640.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
	{ 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f },
	{	0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f } 
};

/* ----- キャラクター構造体 ----- */
struct CHARACTER {
	int x;	// キャラクター位置のx座標
	int y;	// キャラクター位置のy座標
};

/* ----- 当たり判定可視状態 ----- */
const bool IS_HITAREAVISIBLE = true;

#endif

