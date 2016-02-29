// メモリーリーク検知用ヘッダファイル
// これを各ソースファイル(.cpp)のヘッダインクードの末尾でインクルードすることで
// メモリリークの原因箇所を特定することができます。

// 関数 _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) をメイン関数の先頭で呼び出すことでメモリーリークを検知します。
// メモリーリークはデバッグモードのみ機能します。
// メモリリーク発生箇所はデバッグモードの出力に表示されます。

#ifndef __MEMORY_LEAK_H__
#define __MEMORY_LEAK_H__

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// メモリーリーク箇所を起こしているファイル名、行数を表示
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif