// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。

#ifndef __STDAFX_H__
#define __STDAFX_H__

// fopenの警告を消すために定義
#define _CRT_SECURE_NO_DEPRECATE 1

#define WIN32_LEAB_AND_MEAN		// Windowsヘッダーから使用されていない部分を除外します。	

// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>	// TCHAR型C標準ライブラリ
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iterator>
using namespace std;


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include "define.h"
#include "define_game.h"

#endif

