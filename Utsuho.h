/* ====================================
		�EUtsuho.h
			����N���X
===================================== */

#ifndef __UTSUHO_H__
#define __UTSUHO_H__

#include <d3dx9.h>
#include "GameObject.h"

class CUtsuho : public CGameObject{
private:
	int			m_AnimeCount;		// �A�j���[�V�����J�E���^
	int			m_lastAnime;		// �O�t���[���̃A�j���̏��
	float		m_Vy;				// �`���m�̈ړ����x(y����)

public:
	CUtsuho();		// �R���X�g���N�^
	~CUtsuho();		// �f�X�g���N�^	
	void Init();	// �������֐�
	void Anime();	// �A�j���[�V���������֐�
};

#endif