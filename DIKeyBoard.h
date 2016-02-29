/* ===============================================================
	�EDIKeyboard.h
		CDIKeyboad�N���X	: �L�[�{�[�h�N���X
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
	�L�[�{�[�h�N���X : CDIKeyboard�N���X
--------------------------------------------------- */
class CDIKeyBoard {
private:
	static LPDIRECTINPUT8		 m_pDInput;			// DirectInput�I�u�W�F�N�g
	static LPDIRECTINPUTDEVICE8	 m_pDIDevice;		// DirectInput�f�o�C�X�I�u�W�F�N�g
	static BYTE					 m_nowKBBuf[256];	// ���݂̃L�[���
	static BYTE					 m_lastKBBuf[256];	// �P�t���[���O�̃L�[���

public:
	static HRESULT	InitDID();			// DirectInput�f�o�C�X(�L�[�{�[�h)�̍쐬
	static void		CleanUp();			// DirectInput�I�u�W�F�N�g�A�f�o�C�X�J���֐�	
	static HRESULT	UpDate();			// �L�[�{�[�h�̏�Ԃ��擾
	static bool   GetKeyPrs(UINT);				// �L�[�擾�֐�
//	static bool   GetKeyPrsHold(UINT);			// �L�[�擾�֐�
};


#endif