/* ==========================================================
	・TextureManager.cpp
			テクスチャ管理クラスの処理
============================================================= */

#include "stdafx.h"

#include "TextureManager.h"
#include "DxGraphic.h"
#include "WinMain.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

// 静的メンバ初期化
BYTE* CTextureManager::m_pPointer = NULL;			
map<tstring, LPDIRECT3DTEXTURE9> CTextureManager::m_MapTexture;

// ファイルヘッダー構造体
// 128*2 + 4 + 4 = 264 Byte
// Unicodeは半角、全角共に１文字2Byte
struct FILEHeader {
	TCHAR	fileName[128];
	DWORD	fileSize;
	DWORD	address;
};

/* -----------------------------------------------------------
	・CreateTexture() : テクスチャ作成関数
		- datファイルからテクスチャを作成する
		- メモリマップドファイルを使用
		- テクスチャの読み込みはメインループ前に全て読み込む
------------------------------------------------------------ */
bool CTextureManager::CreateTexture() {
	vector<FILEHeader> headerArray;

	/* ------------------- datファイル読み込み ------------------------ */

	// datファイルを開く
	FILE *fp = _tfopen( DATAFILE , _T("rb"));
	if(fp == NULL) {
		MessageBox(NULL, _T("datファイルオープン失敗"), _T("Error"), MB_OK | MB_ICONSTOP);	
		return false;
	}

	// datファイルにあるファイル数を取得
	int fileNum = 0;
	fread(&fileNum, sizeof(int), 1, fp);

	for(int i = 0; i < fileNum; i++) {
		fseek(fp, sizeof(int), SEEK_SET);			// datファイル先頭から4Byte分、ポインタ移動
		fseek(fp, sizeof(FILEHeader)*i, SEEK_CUR);	// FILEHeader分、ポインタ移動

		// ファイル名を取得
		TCHAR ch[128];
		fread(&ch[0], sizeof(TCHAR[128]), 1, fp);
		tstring fName = tstring( ch );

		// ファイルサイズを取得
		DWORD size;
		fread(&size, sizeof(DWORD), 1, fp);

		// ファイルヘッダーだったらheaderArrayに格納
		if(size !=0 && fName.end() != find(fName.begin(), fName.end(), _T('.'))) {
			FILEHeader fHeader;
			_tcscpy(fHeader.fileName, ch);
			fHeader.fileSize = size;

			// ファイルアドレスを取得
			fread(&fHeader.address, sizeof(DWORD), 1, fp);

			back_inserter( headerArray ) = fHeader;
		}
	}

	fclose( fp );	// ファイル読み込み終了


	/* ------------------- メモリマップドファイル ------------------------ */
	HANDLE hFile = CreateFile(DATAFILE, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
	if(hFile == INVALID_HANDLE_VALUE) { 
		MessageBox(NULL, _T("CreateFile失敗"), _T("Error: メモリマップドファイル"), MB_OK | MB_ICONSTOP);	
		return false;		
	}

	// ファイルマッピングオブジェクトを作成
	HANDLE hMap = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, DATAFILE);
	if(hMap <= 0) {	
		MessageBox(NULL, _T("CreateFileMapping失敗"), _T("Error: メモリマップドファイル"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// ポインタを取得
	m_pPointer = (BYTE*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if(m_pPointer == NULL) {
		MessageBox(NULL, _T("MapViewOfFile失敗"), _T("Error: メモリマップドファイル"), MB_OK | MB_ICONSTOP);
		return false;
	}

	/* ------------------- テクスチャ作成 ------------------------- */
	for(UINT i = 0; i < headerArray.size(); i++) {
		LPDIRECT3DTEXTURE9 texture;
		BYTE* ptr = m_pPointer + headerArray[i].address;	// datファイルの先頭からaddress分、ポインタ移動
		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( CDxGraphic::m_pD3DDevice, 
															ptr,
															headerArray[i].fileSize,
															D3DX_DEFAULT_NONPOW2,
															D3DX_DEFAULT_NONPOW2,
															0,
															0,
															D3DFMT_UNKNOWN,
															D3DPOOL_MANAGED,
															D3DX_FILTER_NONE,
															D3DX_DEFAULT,
															0,
															NULL,
															NULL,
															&texture);
		if(FAILED(hr)) {
			return false;
		}

		m_MapTexture.insert( pair<tstring, LPDIRECT3DTEXTURE9>(tstring(headerArray[i].fileName), texture) );		// マップにテクスチャを挿入
	}

	/* -------------------- ブランクテクスチャ作成 --------------------- */
	LPDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTexture( CDxGraphic::m_pD3DDevice,
									512,
									512,
									0,
									0,
									D3DFMT_UNKNOWN,
									D3DPOOL_MANAGED,
									&texture);
	if(FAILED(hr)) {
		return false;
	}

	m_MapTexture.insert( pair<tstring, LPDIRECT3DTEXTURE9>(_T("BlankTex"), texture) );		// マップにブランクテクスチャを挿入

	return true;
}

/* -------------------------------------------------------
	・DeleteTexture() : テクスチャ削除関数
-------------------------------------------------------- */
void CTextureManager::DeleteTexture() {
	// 作成したテクスチャを解放する
	map<tstring, LPDIRECT3DTEXTURE9>::iterator it = m_MapTexture.begin();
	while( it != m_MapTexture.end() ) {
		SAFE_RELEASE( (*it).second );
		it++;
	}

	m_MapTexture.clear();
	UnmapViewOfFile( m_pPointer );	// マッピング解除
	m_pPointer = NULL;
}

/* -------------------------------------------------------
	・GetTexture() : テクスチャgetter関数
-------------------------------------------------------- */
LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(tstring keyName) {
	map<tstring, LPDIRECT3DTEXTURE9>::iterator it = m_MapTexture.find( keyName );
	if(it == m_MapTexture.end()) {
		MessageBox(NULL, _T("指定したテクスチャが存在しません。"), _T("Error: TextureManager"), MB_OK | MB_ICONSTOP);
		PostMessage(GethWnd(), WM_QUIT, 0, 0);	// メインループを抜けて終了
		return NULL;
	}
	return it->second;	// テクスチャを返す
}