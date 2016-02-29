/* ==============================================================================
	・Dx_Graphic.h
		注：このクラスのメンバは全てstaticとし、１つだけ存在するものとする。
			newでインスタンス化しないでください。
============================================================================== */

#ifndef __DXGRAPHIC_H__
#define __DXGRAPHIC_H__

#include <d3dx9.h>		// Direct3D & D3DX
#include <dxerr.h>

class CDxGraphic {
private:
	static PDIRECT3D9				m_pD3D;				// IDirect3D9インターフェイス
	static D3DPRESENT_PARAMETERS	m_D3DPP;			// 使用するディスプレイパラメータ :デバイス動作を設定する構造体
	static D3DPRESENT_PARAMETERS	m_D3DPPWindow;		// D3DDeviceの設定（ウィンドウモード用）
	static D3DPRESENT_PARAMETERS	m_D3DPPFull;		// D3DDeviceの設定（フルスクリーン・モード用）

	static bool					m_FirstTimeChange;	// ウィンドウモード切り替えが初めてか判定するフラグ

public:
	static LPDIRECT3DDEVICE9		m_pD3DDevice;		// DirectX3Dデバイス
	static LPD3DXSPRITE				m_pD3DXSprite;		// スプライト

	static HRESULT		InitD3D(bool);								// Direct3D初期化処理関数
	static void			SetDevice();								// D3Dデバイスに設定を加える関数
	static void			DXCleanUp();								// Direct3D開放関数
	static HRESULT		InitD3DObject();							// スプライトのリセット
	static HRESULT		CleanupD3DObject();							// スプライトの復元
	static void			ResetDevice();								// ロストしたデバイスを復元する関数
	static bool			ChangeDisplayMode(bool, RECT*, int, int);	// ウィンドウモード切り替え関数
};

#endif