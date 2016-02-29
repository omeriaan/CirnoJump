/* ==========================================================
	�EDx_Input.cpp
			DirectInput�N���X�̏���
============================================================= */

#include "stdafx.h"

#include "DIKeyboard.h"
#include "WinMain.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

// �ÓI�����o�̏�����
LPDIRECTINPUT8			CDIKeyBoard::m_pDInput = NULL;
LPDIRECTINPUTDEVICE8	CDIKeyBoard::m_pDIDevice = NULL;
BYTE					CDIKeyBoard::m_nowKBBuf[256];				
BYTE					CDIKeyBoard::m_lastKBBuf[256];

/* ----------------------------------------------------
	�EInitDID()
		- DirectInput�I�u�W�F�N�g�̍쐬
		- DirectInput�f�o�C�X�i�L�[�{�[�h�j�̍쐬
		- �e��ݒ�
----------------------------------------------------- */
HRESULT	CDIKeyBoard::InitDID() {
	HRESULT hr;

	// DirectInput�I�u�W�F�N�g�̍쐬
	hr = DirectInput8Create(GethInstance(), DIRECTINPUT_VERSION, 
					IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if(FAILED(hr)) {
		return hr;
	}

	// DirectInput�f�o�C�X�̍쐬
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr)) {
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�(�L�[�{�[�h�p�t�H�[�}�b�g)
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) {
		return hr;
	}

	// �������[�h�̐ݒ�i�t�H�A�O�����h���[�h & ��r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(GethWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(hr)) {
		return hr;
	}

	// �L�[����0�N���A
	ZeroMemory(m_nowKBBuf, sizeof(m_nowKBBuf));
	ZeroMemory(m_lastKBBuf, sizeof(m_lastKBBuf));

	// ���͐���J�n
	m_pDIDevice->Acquire();
	return hr;
}

/* ----------------------------------------------------
	�ECleanUp()
		- DirectInput�I�u�W�F�N�g�A�f�o�C�X�̊J��
----------------------------------------------------- */
void CDIKeyBoard::CleanUp() {

	m_pDIDevice->Unacquire();	// ���͂̒�~
	SAFE_RELEASE(m_pDIDevice);	// DirectInput�f�o�C�X���J��
	m_pDIDevice = NULL;

	// DirectInput�I�u�W�F�N�g�̊J��
	SAFE_RELEASE(m_pDInput);
	m_pDInput = NULL;
}

/* -----------------------------------------------------
	�EUpDate()
		- �f�o�C�X���X�g�̊m�F��
		�@�P�t���[���O�̃L�[�����X�V
------------------------------------------------------ */
HRESULT CDIKeyBoard::UpDate() {
	// ���̃L�[�����P�t���[���O�ɃR�s�[���Č��݂̃L�[�����N���A
	memcpy(m_lastKBBuf, m_nowKBBuf, sizeof(m_nowKBBuf));
	ZeroMemory(m_nowKBBuf, sizeof(m_nowKBBuf));

	// �f�o�C�X���X�g�΍�
	HRESULT hr = m_pDIDevice->GetDeviceState(sizeof(m_nowKBBuf), m_nowKBBuf);
	if(hr == DIERR_INPUTLOST) {
		while(m_pDIDevice->Acquire() == DIERR_INPUTLOST);
	}

	return hr;
}

/* -----------------------------------------------------------
	�EGetKeyPrs()
		- �����ɗ^����ꂽ�L�[�����݉�����Ă��邩���m�F����
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
	�EGetKeyPrsHold()
		- �����ɗ^����ꂽ�L�[���������ςȂ����ǂ������m�F����
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