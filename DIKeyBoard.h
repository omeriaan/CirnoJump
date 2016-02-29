/* ===============================================================
	・DIKeyboard.h
		CDIKeyboadクラス	: キーボードクラス
================================================================ */

#ifndef __DXINPUT_H__
#define __DXINPUT_H__

// DirectInput Version
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x800
#endif

#include <windows.h>
#include <dinput.h>

/* ---------------------------------------------------
	キーボードクラス : CDIKeyboardクラス
--------------------------------------------------- */
class CDIKeyBoard {
private:
	static LPDIRECTINPUT8		 m_pDInput;			// DirectInputオブジェクト
	static LPDIRECTINPUTDEVICE8	 m_pDIDevice;		// DirectInputデバイスオブジェクト
	static BYTE					 m_nowKBBuf[256];	// 現在のキー情報
	static BYTE					 m_lastKBBuf[256];	// １フレーム前のキー情報

public:
	static HRESULT	InitDID();			// DirectInputデバイス(キーボード)の作成
	static void		CleanUp();			// DirectInputオブジェクト、デバイス開放関数	
	static HRESULT	UpDate();			// キーボードの状態を取得
	static bool   GetKeyPrs(UINT);				// キー取得関数
//	static bool   GetKeyPrsHold(UINT);			// キー取得関数
};


#endif