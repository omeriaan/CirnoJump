/* ==========================================================
	�EFPSControl.h
			�t���[���Ǘ��N���X
============================================================= */

#ifndef __FPSCONTROL_H__
#define __FPSCONTROL_H__

#include <windows.h>

/* ---------------------------------------------------
	�t���[���Ǘ��N���X : CFpsControl�N���X
--------------------------------------------------- */
class CFpsControl {
private:
	DWORD	m_lastTime;				// �O�̑��莞��
	int		m_frameCount;			// �t���[���J�E���^�[
	double	m_frameTime;			// �P�t���[���ɂ����鎞��
	int		m_FPS;					// �P�b�Ԃ�����̃t���[��������(����)
	int		m_SkipCount;			// �X�L�b�v�J�E���^�[
	int		m_SkipRate;				// �P�b�Ԃ�����̃t���[���X�L�b�v���N������
	bool	m_isFrameSkip;			// �t���[���X�L�b�v�t���O(true:�L false:��)
	bool	m_isDraw;				// �`��t���O

public:
	CFpsControl();					// �R���X�g���N�^
	~CFpsControl();					// �f�X�g���N�^
	void	InitFPS();				// ����������
	void	ControlFPS();			// �t���[�����䏈��
	bool	GetDrawFrag();			// �`��t���Ogetter
	int		GetFPS();				// FPSgetter
	int		GetSkipRate();			// �X�L�b�v���[�ggetter
};


#endif