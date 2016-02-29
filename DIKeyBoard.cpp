/* ==========================================================
	・Dx_Input.cpp
			DirectInputクラスの処理
============================================================= */

#include "stdafx.h"

#include "DIKeyboard.h"
#include "WinMain.h"

#include "Memory_Leak.h"	// メモリーリーク検知用

// 静的メンバの初期化
LPDIRECTINPUT8			CDIKeyBoard::m_pDInput = NULL;
LPDIRECTINPUTDEVICE8	CDIKeyBoard::m_pDIDevice = NULL;
BYTE					CDIKeyBoard::m_nowKBBuf[256];				
BYTE					CDIKeyBoard::m_lastKBBuf[256];

/* ----------------------------------------------------
	・InitDID()
		- DirectInputオブジェクトの作成
		- DirectInputデバイス（キーボード）の作成
		- 各種設定
----------------------------------------------------- */
HRESULT	CDIKeyBoard::InitDID() {
	HRESULT hr;

	// DirectInputオブジェクトの作成
	hr = DirectInput8Create(GethInstance(), DIRECTINPUT_VERSION, 
					IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if(FAILED(hr)) {
		return hr;
	}

	// DirectInputデバイスの作成
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr)) {
		return hr;
	}

	// データフォーマットの設定(キーボード用フォーマット)
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) {
		return hr;
	}

	// 協調モードの設定（フォアグランドモード & 非排他モード）
	hr = m_pDIDevice->SetCooperativeLevel(GethWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(hr)) {
		return hr;
	}

	// キー情報を0クリア
	ZeroMemory(m_nowKBBuf, sizeof(m_nowKBBuf));
	ZeroMemory(m_lastKBBuf, sizeof(m_lastKBBuf));

	// 入力制御開始
	m_pDIDevice->Acquire();
	return hr;
}

/* ----------------------------------------------------
	・CleanUp()
		- DirectInputオブジェクト、デバイスの開放
----------------------------------------------------- */
void CDIKeyBoard::CleanUp() {

	m_pDIDevice->Unacquire();	// 入力の停止
	SAFE_RELEASE(m_pDIDevice);	// DirectInputデバイスを開放
	m_pDIDevice = NULL;

	// DirectInputオブジェクトの開放
	SAFE_RELEASE(m_pDInput);
	m_pDInput = NULL;
}

/* -----------------------------------------------------
	・UpDate()
		- デバイスロストの確認と
		　１フレーム前のキー情報を更新
------------------------------------------------------ */
HRESULT CDIKeyBoard::UpDate() {
	// 今のキー情報を１フレーム前にコピーして現在のキー情報をクリア
	memcpy(m_lastKBBuf, m_nowKBBuf, sizeof(m_nowKBBuf));
	ZeroMemory(m_nowKBBuf, sizeof(m_nowKBBuf));

	// デバイスロスト対策
	HRESULT hr = m_pDIDevice->GetDeviceState(sizeof(m_nowKBBuf), m_nowKBBuf);
	if(hr == DIERR_INPUTLOST) {
		while(m_pDIDevice->Acquire() == DIERR_INPUTLOST);
	}

	return hr;
}

/* -----------------------------------------------------------
	・GetKeyPrs()
		- 引数に与えられたキーが現在押されているかを確認する
------------------------------------------------------------ */
bool CDIKeyBoard::GetKeyPrs(UINT keyCode) {
	if(m_nowKBBuf[keyCode] & 0x80) {
		return true;
	}
	else {
		return false;
	}
}

/* ------------------------------------------------------------
	・GetKeyPrsHold()
		- 引数に与えられたキーが押しっぱなしかどうかを確認する
------------------------------------------------------------- */
/*
bool CDIKeyBoard::GetKeyPrsHold(UINT keyCode) {
	if((m_nowKBBuf[keyCode] & 0x80) && (m_lastKBBuf[keyCode] & 0x80)) {
		return true;
	}
	else {
		return false;
	}
}
*/