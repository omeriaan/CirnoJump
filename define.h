/* ===============================================================
	・define.h
		開発に必要なマクロ、定数をまとめたヘッダファイル
================================================================ */

#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <tchar.h>	// TCHAR型C標準ライブラリ

// tchar型のstring
typedef std::basic_string<TCHAR> tstring;					// tstring型
typedef std::basic_ostringstream<TCHAR> tostringstream;		// tostringstream型	
typedef std::basic_istringstream<TCHAR> tistringstream;		// tistringstream型

/* ----- マクロ ----- */
#define SAFE_RELEASE(x) { if(x) x->Release(); }	// Direct3D開放マクロ :RELEASE

#endif