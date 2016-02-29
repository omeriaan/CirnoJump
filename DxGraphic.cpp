/* ============================================================
	・Dx_Graphic.cpp
			DirectX3D9関連の処理を行う
============================================================= */

#include "stdafx.h"

#include "DxGraphic.h"
#include "WinMain.h"
#include "Game.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

// 静的メンバの初期化
PDIRECT3D9				CDxGraphic::m_pD3D = NULL;				
D3DPRESENT_PARAMETERS	CDxGraphic::m_D3DPP;
D3DPRESENT_PARAMETERS	CDxGraphic::m_D3DPPWindow;
D3DPRESENT_PARAMETERS	CDxGraphic::m_D3DPPFull;
LPDIRECT3DDEVICE9		CDxGraphic::m_pD3DDevice = NULL;
LPD3DXSPRITE			CDxGraphic::m_pD3DXSprite = NULL;
bool					CDxGraphic::m_FirstTimeChange = true;

/* --------------------------------------------------
			Direct3D初期化関数 :InitD3D()
-------------------------------------------------- */
HRESULT CDxGraphic::InitD3D(bool bWindow) {
	D3DDISPLAYMODE	dmode;	//ディスプレイモード

	/* ----- Direct3Dオブジェクトの生成 ----- */
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL) {
		return DXTRACE_ERR(_T("InitDXGraphics Direct3DCreate9"), E_FAIL);
	}

	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode);		// 現在のディスプレイモードデータ取得

	/* ----- D3DPRESENT_PARAMETERS構造体(ウィンドウモード用)の設定 ----- */
	ZeroMemory(&m_D3DPPWindow, sizeof(m_D3DPPWindow));						// 0クリアで初期化
	m_D3DPPWindow.BackBufferFormat			= D3DFMT_UNKNOWN;				// バックバッファフォーマット（現在の画面モードを使用）
	m_D3DPPWindow.BackBufferWidth			= 0;							// 横ドット幅設定(0:対応付けられているクライアントエリアのサイズ)	
	m_D3DPPWindow.BackBufferHeight			= 0;							// 縦ドット幅設定(0:対応付けられているクライアントエリアのサイズ)
	m_D3DPPWindow.BackBufferCount			= 1;							// バックバッファの数
	m_D3DPPWindow.SwapEffect				= D3DSWAPEFFECT_DISCARD;		// フリップの方法（通常はこの定数でよい）
	m_D3DPPWindow.EnableAutoDepthStencil	= TRUE;							// ステンシルバッファの有無(TRUE:有 / FALSE:無)
	m_D3DPPWindow.AutoDepthStencilFormat	= D3DFMT_D16;					// ステンシルフォーマット
	m_D3DPPWindow.Windowed					= TRUE;							// ウィンドウモードの設定

	/* ----- D3DPRESENT_PARAMETERS構造体(フルスクリーンモード用)の設定 ----- */
	ZeroMemory(&m_D3DPPFull, sizeof(m_D3DPPFull));						// 0クリアで初期化
	m_D3DPPFull.BackBufferFormat		= D3DFMT_X8R8G8B8;				// バックバッファフォーマット
	m_D3DPPFull.BackBufferWidth			= SIZEFULL_WIDTH;				// 横ドット幅設定	
	m_D3DPPFull.BackBufferHeight		= SIZEFULL_HEIGHT;				// 縦ドット幅設定
	m_D3DPPFull.BackBufferCount			= 1;							// バックバッファの数
	m_D3DPPFull.SwapEffect				= D3DSWAPEFFECT_DISCARD;		// フリップの方法（通常はこの定数でよい）
	m_D3DPPFull.EnableAutoDepthStencil	= TRUE;							// ステンシルバッファの有無(TRUE:有 / FALSE:無)
	m_D3DPPFull.AutoDepthStencilFormat	= D3DFMT_D16;					// ステンシルフォーマット
	m_D3DPPFull.Windowed				= FALSE;						// ウィンドウモードの設定
	

	/* ----- デバイスオブジェクトの生成 ----- */
	if( bWindow ) {
		m_D3DPP = m_D3DPPWindow;
	}
	else {
		m_D3DPP = m_D3DPPFull;
	}

	// 「HAL&ハードウェア頂点処理」デバイスを生成
	HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GethWnd(), 
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPP, &m_pD3DDevice);
	if( FAILED(hr) ) {	// もし生成に失敗したら
		// 「HAL&ソフトウェア頂点処理」デバイスを生成
		hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GethWnd(), 
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPP, &m_pD3DDevice);
		if( FAILED(hr) ) {	// もし生成に失敗したら
			// 「REF&ソフトウェア頂点処理」デバイスを作成
			hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GethWnd(), 
							D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPP, &m_pD3DDevice);
			if( FAILED(hr) ) {	// どのデバイスも取得できなかったら
				return DXTRACE_ERR(_T("InitDXGraphics CreateDevice"), hr);
			}
		}
	}

	/* ----- スプライトの初期化 ----- */
	hr = D3DXCreateSprite(m_pD3DDevice, &m_pD3DXSprite);				// スプライト作成
	if( FAILED(hr) ) {
		return DXTRACE_ERR(_T("InitDXGraphics D3DXCreateSprite"), hr);
	}

	SetDevice();	// D3DDeviceに設定を加える

	return S_OK;
}	

/* ----------------------------------------------------------
	・SetDevice() : D3DDeviceに設定を加える関数
----------------------------------------------------------- */
void CDxGraphic::SetDevice() {

	/* ----- ポリゴンのアルファブレンディングの設定 ----- */
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );					// アルファブレンドを有効にする
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND         , D3DBLEND_SRCALPHA );		// 描画元のアルファブレンディング設定
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND        , D3DBLEND_INVSRCALPHA );	// 描画先のアルファブレンディング設定

	/* ----- 線形補完によりポリゴンのジャギーを失くす ----- */
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	/* ----- ラップテクスチャアドレッシングモードを設定　----- */
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );		// u軸にラップ
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );		// v軸にラップ
}


/* ----------------------------------------------------------
			Dirext3D開放関数 :DXCleanUp()
---------------------------------------------------------- */
void CDxGraphic::DXCleanUp() {
	SAFE_RELEASE( m_pD3DXSprite );		// スプライトの解放
	m_pD3DXSprite = NULL;
	SAFE_RELEASE( m_pD3DDevice );		// デバイスオブジェクトの解放
	m_pD3DDevice = NULL;
	SAFE_RELEASE( m_pD3D );				// DirectX9オブジェクトの解放
	m_pD3D = NULL;
}


/* ----------------------------------------------------------------------------------
	D3Dに管理されないオブジェクトの初期化(スプライトのリセット等) :InitD3DObject()
---------------------------------------------------------------------------------- */
HRESULT CDxGraphic::InitD3DObject() {
	// スプライトの処理
	if(m_pD3DXSprite) {
		m_pD3DXSprite->OnResetDevice();
	}

	return S_OK;
}

/* ----------------------------------------------------------------------------------
	D3Dに管理されないオブジェクトの終了処理(スプライトの復元等) :CleanupD3DObject()
---------------------------------------------------------------------------------- */
HRESULT CDxGraphic::CleanupD3DObject() {
	// スプライトの処理
	if(m_pD3DXSprite) {
		m_pD3DXSprite->OnLostDevice();
	}

	return S_OK;
}



/* ----------------------------------------------------------
		ロストしたデバイスを復元する関数 :ResetDevice()
---------------------------------------------------------- */
void CDxGraphic::ResetDevice() {
	HRESULT hr;
	Sleep(100);										// 0.1秒待つ

	hr = m_pD3DDevice->TestCooperativeLevel();		// デバイス状態のチェック	
	if(FAILED(hr)) {
		if(hr == D3DERR_DEVICENOTRESET) {			// もしリセット可能な状態なら復元処理開始
			CleanupD3DObject();						// リソースを解放

			hr = m_pD3DDevice->Reset(&m_D3DPP);		// デバイスを復元
			if(FAILED(hr)){
				if(hr != D3DERR_DEVICELOST) {
					DXTRACE_ERR(_T("ChangeDisplayMode Reset"), hr);
					return;
				}
			}

			InitD3DObject();						// 解放したリソースを再構築
		}
	}
}


/* -----------------------------------------------------------------------------
	ウィンドウモード<-->フルスクリーンモード切り替え関数 :ChangeDisplayMode()
----------------------------------------------------------------------------- */
bool CDxGraphic::ChangeDisplayMode(bool bWindow, RECT* rectWindow, int InitWndPosX, int InitWndPosY) {

	if( !bWindow ) {							// フルスクリーン -> ウィンドウの場合
		m_D3DPP = m_D3DPPWindow;				// デバイスパラメータをウィンドウモード用に差し替え
	}
	else {										// ウィンドウ -> フルスクリーンの場合
		m_D3DPP = m_D3DPPFull;					// デバイスパラメータをフルスクリーンモード用に差し替え
		GetWindowRect(GethWnd(), rectWindow);	// ウィンドウモードの最後の位置、サイズを取得	
	}
	
	CleanupD3DObject();									// リソースを解放
	HRESULT hr = m_pD3DDevice->Reset(&m_D3DPP);			// デバイスを復元
	if(FAILED(hr)) {
		if(hr == D3DERR_DEVICELOST) {
			MessageBox(NULL, _T("DEVICELOST"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == D3DERR_DRIVERINTERNALERROR){
			MessageBox(NULL, _T("DRIVERINTERNALERROR"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == D3DERR_INVALIDCALL) {
			MessageBox(NULL, _T("INVALIDCALL"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == D3DERR_OUTOFVIDEOMEMORY) {
			MessageBox(NULL, _T("OUTOFVIDEOMEMORY"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == E_OUTOFMEMORY) {
			MessageBox(NULL, _T("OUROFMEMORY"), _T("DeviceLostError"), MB_OK);
		}

		DXTRACE_ERR(_T("ChangeDisplayMode Reset"), hr);
		return false;							// デバイスの復元に失敗
	}

	InitD3DObject();					// 解放したリソースを再構築

	if( !bWindow ) {					// フルスクリーン -> ウィンドウの場合
		RECT rect;
		rect.left	= rectWindow->left;
		rect.top	= rectWindow->top;
		if( m_FirstTimeChange ) {					// もし初期ウィンドウモードがフルスクリーンの時
			rect.left	= InitWndPosX;				// ウィンドウの配置位置をディスプレイの中央にする
			rect.top	= InitWndPosY;	
		}

		SetWindowLong(GethWnd(), GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE);
		SetWindowPos(GethWnd(), HWND_TOP,
			rect.left, rect.top,
			rectWindow->right - rectWindow->left,
			rectWindow->bottom -rectWindow->top,
			SWP_SHOWWINDOW);
	}
	else {											// ウィンドウ -> フルスクリーンの場合
		SetWindowLong(GethWnd(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}

	SetDevice();	// 復元したD3DDeviceに設定を加える

	m_FirstTimeChange = false;						// 一回でもChangeDisplayModeを実行したらfalseにする

	return true;
}

