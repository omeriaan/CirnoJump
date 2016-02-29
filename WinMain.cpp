/* =============================================================
	・WinMain.cpp
			ウィンドウの初期化、メイン関数を持つ
============================================================== */

#include "stdafx.h"

#include "DxGraphic.h"
#include "DIKeyboard.h"
#include "FPSControl.h"
#include "TextureManager.h"
#include "Game.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

/* ----- グローバル変数宣言 ----- */
HWND		hWnd;			 // ウィンドウハンドル
HINSTANCE	g_hInstance;	 // ウィンドウインスタンス

bool		g_bWindow			= true;				// ウィンドウモードの指定（TRUE:ウィンドウモード / FALSE:フルスクリーン）
bool		g_bActive			= false;			// アクティブ状態フラグ(TRUE:アクティブ状態 / FALSE:非アクティブ状態)
bool		g_bDeviceLost		= false;			// デバイスロストフラグ(TRUE:デバイスロスト状態 / FALSE:非デバイスロスト状態)
RECT		g_rectWindow;							// ウィンドウモードでの最後の位置、サイズ
int			g_InitWndPosX;							// ウィンドウの初期位置X座標（ディスプレイの中央） 
int			g_InitWndPosY;							// ウィンドウの初期位置Y座標（ディスプレイの中央）

CGame*		 g_pGame			= NULL;				// Gameオブジェクト
CFpsControl* g_pFPSController	= NULL;				// FPS管理オブジェクト

/* ----- プロトタイプ宣言 ----- */
LRESULT		CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// ウィンドウプロシージャ
bool		InitApp(HINSTANCE);								// ウィンドウ作成関数
void		CleanUp();										// 終了時の解放処理	

/* ------ getter関数 ------ */
HWND		GethWnd()	   { return hWnd; }			// ウィンドウハンドルgetter
HINSTANCE	GethInstance() { return g_hInstance; }	// ウィンドウインスタンスgetter


/* -------------------------------------
			メイン関数
-------------------------------------- */
int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszArgs, int nWinMode) {
	// メモリリークを検出。（デバッグモードのみ）
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	

	g_hInstance = hInst;
	MSG msg;	// メッセージ構造体変数


	// 表示するウィンドウの定義、登録、表示
	// もしInitApp関数の戻り値が0なら、エラー値を戻り値としてメイン関数を終了する
	if (!InitApp(hInst)) {	// InitApp関数を呼び出し、
		MessageBox(NULL, _T("アプリケーションの初期化に失敗しました"), _T("Error"), MB_OK | MB_ICONSTOP);
		return false;			// 正常に終了すれば次にメッセージループへ
	}

	// DirectX9の初期化
	if( FAILED(CDxGraphic::InitD3D(g_bWindow)) ) {
		MessageBox(NULL, _T("DirectX9デバイスの初期化に失敗"), _T("Error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// DirectInput8の初期化
	if( FAILED(CDIKeyBoard::InitDID()) ) {
		MessageBox(NULL, _T("DirectInput8デバイスの初期化に失敗"), _T("Error"), MB_OK | MB_ICONSTOP);
		CleanUp();
		return false;
	}

	// テクスチャを作成
	if( !CTextureManager::CreateTexture() ) {
		MessageBox(NULL, _T("テクスチャの作成に失敗"), _T("Error"), MB_OK | MB_ICONSTOP);
		CleanUp();
		return false;
	}

	// Gameオブジェクト作成
	g_pGame = new CGame();
	// FPS管理オブジェクト作成
	g_pFPSController = new CFpsControl();
	g_pFPSController->InitFPS();

	LPDIRECT3DDEVICE9 D3DDevice = CDxGraphic::m_pD3DDevice;		// DxGraphicデバイスを取得

	// メインループ
	while( true ) {
		// メッセージがあるか確認する
		if( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) ) {
			if( !GetMessage(&msg, NULL, 0, 0) )	break;	// メッセージがWM_QUITだったらループを抜ける
			TranslateMessage(&msg);						// キーボード利用を可能にするために必要
			DispatchMessage(&msg);						// ウィンドウプロシージャにメッセージを送る
		}
		else {
			if( g_bActive ){		// アクティブ状態の時

				if( g_bDeviceLost ) {				// デバイスロスト状態の時
					CDxGraphic::ResetDevice();		// デバイスを復元する
					g_bDeviceLost = false;			// デバイスロストフラグをfalse
				}

				CDIKeyBoard::UpDate();				// キーボードを監視

				D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );	// シーンのクリア(白)
				D3DDevice->BeginScene();															// シーン描画開始
				g_pGame->UpDate();																	// シーンの描画
				D3DDevice->EndScene();																// シーン描画終了

				g_pFPSController->ControlFPS();														// FPS管理
				
				if(g_pFPSController->GetDrawFrag()) {
					/* ----- デバッグモードの時、FPSとスキップレートを表示 ------ */			
					#ifdef _DEBUG
						tostringstream os;
						os << TITLE 
							<< " - FPS = " << g_pFPSController->GetFPS() << _T(",")
							<< "SkipRate = " << g_pFPSController->GetSkipRate() << _T("\n");
						SetWindowText(hWnd, os.str().c_str());
					#endif

					HRESULT hr = D3DDevice->Present( NULL, NULL, NULL, NULL );	// シーンの表示
					if(hr == D3DERR_DEVICELOST) {								// もしデバイスがロストしていたら
						g_bDeviceLost = true;									// デバイスロストフラグをtrue
					}
				}

				Sleep(1);
			}
			else {					// 非アクティブ状態の時
				WaitMessage();		// メッセージが来るまでループを一時停止
			}
		}
	}
	
	CleanUp();					// 解放処理
	return msg.wParam;
}

/* ----------------------------------------------------------
	終了時の解放処理	
----------------------------------------------------------- */
void CleanUp() {
	delete g_pGame;						// Gameオブジェクトを解放
	delete g_pFPSController;			// FPS管理オブジェクトを解放
	CTextureManager::DeleteTexture();	// テクスチャを削除
	CDxGraphic::DXCleanUp();			// DxGraphiを解放
	CDIKeyBoard::CleanUp();				// DIKeyboardを解放
}

/* ----------------------------------------------------------
	ウィンドウプロシージャ関数（WindowProcedure）:WndProc()
	メッセージ処理を行う
---------------------------------------------------------- */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_ACTIVATE:								// アクティブ状態が変化した時
			g_bActive = (LOWORD(wParam) != 0);			// アクティブ状態フラグを変更
			break;

		case WM_SYSKEYDOWN:								// システムキー（Altキー）が押された時
			switch( wParam ) {
				case VK_RETURN:							// Alt + Enterが押された時
					// ウィンドウモード <--> フルスクリーンの切り替え
					bool hr = CDxGraphic::ChangeDisplayMode(g_bWindow, 
															&g_rectWindow,
															g_InitWndPosX,
															g_InitWndPosY	);

					if(!hr) {
						g_bDeviceLost = true;
					}
					else {
						g_bWindow = !g_bWindow;						// フラグを反転
					}
					break;
			}
			break;

		case WM_SYSCOMMAND:								// システムコマンドメッセージ(ウィンドウ右上の最小化、最大化等)が来たら
			switch( wParam ) {
				case SC_MAXIMIZE:						// 最大化ボタンをクリックした時，フルスクリーンモードに切り替え
					bool hr = CDxGraphic::ChangeDisplayMode(g_bWindow, 
															&g_rectWindow,
															g_InitWndPosX,
															g_InitWndPosY );
					if(!hr) {
						g_bDeviceLost = true;
					}
					else {
						g_bWindow = !g_bWindow;			// フラグを反転
					}
					break;
			}
			break;

		case WM_DESTROY:								// 閉じるボタンをクリックした時
			PostQuitMessage(0);							// WM_QUITメッセージを発行
			break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);	// デフォルト処理
}


/* --------------------------------------------------
	InitApp()
	表示するウィンドウの定義、登録、表示
	戻り値:正常終了のとき１、異常終了の時０
-------------------------------------------------- */
bool InitApp(HINSTANCE hInst) {
	WNDCLASSEX wc;			//ウィンドウクラス構造体

	// ウィンドウクラスを定義する
	wc.cbSize			= sizeof(WNDCLASSEX);		// WNDCLASSEX構造体のサイズを設定
	wc.style			= NULL;						// ウィンドウスタイル
	wc.lpfnWndProc		= WndProc;					// ウィンドウ関数
	wc.cbClsExtra		= 0;						// 通常は使わない（0にしておく）
	wc.cbWndExtra		= 0;						// 通常は使わない（0にしておく）
	wc.hInstance		= hInst;					// このインスタンスへのハンドル
	wc.hIcon			= NULL;						// ラージアイコン（なし）
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// カーソルスタイル
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	// ウィンドウの背景（黒）
	wc.lpszMenuName		= NULL;						// メニュー（なし）
	wc.lpszClassName	= NAME;						// ウィンドウクラス名
	wc.hIconSm			= NULL;						// スモールアイコン（なし）

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wc)) {
		return (FALSE);
	}

	// ウィンドウ全体のサイズを設定する
	SetRect(&g_rectWindow, 0, 0, SIZEWINDOW_WIDTH, SIZEWINDOW_HEIGHT);
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, FALSE);
	g_rectWindow.right	= g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom = g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top	= 0;
	g_rectWindow.left	= 0;

	// ウィンドウ作成位置を計算する（ディスプレイの中央に配置）
	g_InitWndPosX = (GetSystemMetrics( SM_CXSCREEN ) - SIZEWINDOW_WIDTH) / 2;
	g_InitWndPosY = (GetSystemMetrics( SM_CYSCREEN ) - SIZEWINDOW_HEIGHT) / 2;

	RECT rect;										// top,left : 位置 / right : ウィンドウの幅 / bottom : ウィンドウの高さ
	if( g_bWindow ) {								// ウィンドウモードの位置とサイズ設定
		rect.top	= g_InitWndPosY;
		rect.left	= g_InitWndPosX;
		rect.right	= g_rectWindow.right;
		rect.bottom = g_rectWindow.bottom;
	}
	else {											// フルスクリーンモードの位置とサイズ設定
		rect.top	= 0;
		rect.left	= 0;
		rect.right	= SIZEFULL_WIDTH;
		rect.bottom = SIZEFULL_HEIGHT;
	}

	/* ----- ウィンドウを生成 ----- */
	hWnd = CreateWindow(
		NAME,									// ウィンドウクラスの名前
		TITLE,									// ウィンドウタイトル
		g_bWindow ? WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME : WS_POPUP,	// ウィンドウスタイル
		rect.left,									// ウィンドウの左隅Ｘ座標
		rect.top,									// ウィンドウの左隅Ｙ座標
		rect.right,									// ウィンドウの幅
		rect.bottom,								// ウィンドウの高さ
		NULL,										// 親ウィンドウ（なし）
		NULL,										// メニュー（なし）
		hInst,										// このプログラムのインスタンスのハンドル
		NULL										// 追加引数（なし）
	);

	/* ----- ウィンドウ表示 ----- */
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return true;
}



