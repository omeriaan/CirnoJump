/* ====================================
		�ECirno.h
			�`���m�N���X
===================================== */

#ifndef __CIRNO_H__
#define __CIRNO_H__

#include <d3dx9.h>
#include "GameObject.h"

// �`���m�̏�Ԃ̎��
enum CirnoState {
	Cirno_Run,				// �����Ă���
	Cirno_JumpUp,			// �W�����v���i�㏸�j
	Cirno_JumpDown			// �W�����v���i���~�j
};

class CCirno : public CGameObject{
private:
	CirnoState  m_State;			// ���݂̃`���m�̏��
	int			m_AnimeCount;		// �A�j���[�V�����J�E���^
	int			m_lastAnime;		// �O�t���[���̃A�j���̏��
	float		m_Vy;				// �`���m�̈ړ����x(y����)

public:
	CCirno();		// �R���X�g���N�^
	~CCirno();		// �f�X�g���N�^	
	void Init();	// �������֐�
	void Jump();	// �W�����v�A�N�V�����֐�
	void Anime();	// �A�j���[�V���������֐�
};

#endif