/* ==========================================================
	�EFPSControl.cpp
			�t���[������
============================================================= */

#include "stdafx.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "FPSControl.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

/* ----------------------------------------------
			�R���X�g���N�^
---------------------------------------------- */
CFpsControl::CFpsControl() 
	: m_frameTime(1000.0 / REQUEST_FPS),
	  m_isFrameSkip(IS_FRAMESKIP),
	  m_frameCount( 0 ),
	  m_FPS( 0 ),
	  m_SkipCount( 0 ),
	  m_SkipRate( 0 ),
	  m_isDraw( true )
{
	timeBeginPeriod(1);				// �^�C�}�[(timeGetTime)�̐��x�����コ����
}

/* ----------------------------------------------
			�f�X�g���N�^
---------------------------------------------- */
CFpsControl::~CFpsControl() {
	timeEndPeriod(1);			
}


/* ----------------------------------------------
	�EInitFPS()
		����������
---------------------------------------------- */
void CFpsControl::InitFPS() {
	m_lastTime = timeGetTime();
}


/* ----------------------------------------------
	�EControlFPS()
		�t���[�����䏈��
---------------------------------------------- */
void CFpsControl::ControlFPS() {
	m_frameCount++;

	// �t���[���X�L�b�v����
	// ���݂̎��������̃t���[�����Ԃ��I�[�o�[���Ă��܂����ꍇ
	if( m_isFrameSkip && timeGetTime() > (DWORD)(m_lastTime + (m_frameCount+1) * m_frameTime) ) {
		m_isDraw = false;				// �`��t���O��false�ɂ���(�`�悵�Ȃ�)
		m_SkipCount++;
	}
	else {
		// �ҋ@����
		while(timeGetTime() <= (DWORD)(m_lastTime + m_frameCount * m_frameTime)) {
			Sleep(1);
		}
		m_isDraw = true;				// �`��t���O��true�ɂ���(�`�悷��)
	}

	// ���ݎ������O�ɑ��肵������(m_lastTime)���P�b�ȏ�o�߂��Ă�����
	if(timeGetTime() - m_lastTime >= 1000) {
		m_lastTime = timeGetTime();		// ���莞�����X�V
		m_FPS = m_frameCount;			// �t���[�����[�g���X�V(�P�b������̃t���[��������:���z�l60fps)
		m_SkipRate = m_SkipCount;		// �X�L�b�v���[�g���X�V
		m_frameCount = 0;
		m_SkipCount  = 0;

		/* ----- �f�o�b�O���[�h�̎��AFPS�ƃX�L�b�v���[�g��\�� ------ */
/*
		#ifdef _DEBUG
			tostringstream os;
			os << _T("FPS = ") << m_FPS << _T(", SkipRate = ") << m_SkipRate << _T("\n");
			OutputDebugString( os.str().c_str() );
		#endif
*/
	}
}

/* ----------------------------------------------
	�EGetDrawFrag()
		�`��t���Ogetter
---------------------------------------------- */
bool CFpsControl::GetDrawFrag() {
	return m_isDraw;
}

/* ----------------------------------------------
	�EGetFPS()
		FPSgetter
---------------------------------------------- */
int CFpsControl::GetFPS() {
	return m_FPS;
}

/* ----------------------------------------------
	�EGetSkipRate()
		�t���[���X�L�b�vgetter
---------------------------------------------- */
int CFpsControl::GetSkipRate() {
	return m_SkipRate;
}