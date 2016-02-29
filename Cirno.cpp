/* ============================================================
	�ECirno.cpp
			�`���m�̏���
============================================================= */
#include "stdafx.h"

#include "DxGraphic.h"
#include "DIKeyBoard.h"
#include "TextureManager.h"
#include "Cirno.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		�R���X�g���N�^
------------------------------------------ */
CCirno::CCirno() 
{	
	Init();	// ����������
}

/* -----------------------------------------
		�f�X�g���N�^
------------------------------------------ */
CCirno::~CCirno() {
}

/* -----------------------------------------
	�EInit() :�@�������֐�
------------------------------------------ */
void CCirno::Init() {
	
	/* ----- �`���m�̏����ݒ� ----- */
	m_Chara.x = 64;			// ����x���W�ʒu				
	m_Chara.y = 374;		// ����y���W�ʒu
	m_State = Cirno_Run;	// ������

	m_Vy = 0.0f;			// �ړ����x(y��)
	m_AnimeCount = 0;		// �A�j���[�V�����J�E���g������
	m_lastAnime = 0;		// �O�t���[���̃A�j���̏��

	m_textureName = _T("img\\Cirno.dds");	// �e�N�X�`����

	/* ----- Draw�ݒ� ----- */
	RECT rc = {0, 0, 128, 128};
	m_rectSize = rc;	// ��`�T�C�Y
	m_rect = rc;		// �����\����` {left, top, right, bottom : 0, 0, 128, 128}

	// ���������蔻��
	m_hitRect.top = m_Chara.y - 50;
	m_hitRect.left = m_Chara.x - 20;
	m_hitRect.bottom = m_Chara.y + 45;
	m_hitRect.right = m_Chara.x + 30;

	// ��`�̒��S���W
	m_center.x = (float)rc.right/2;
	m_center.y = (float)rc.bottom/2;
	m_center.z = 0;

}

/* -------------------------------------------
	�EJump() :�@�W�����v�A�N�V���������֐�
-------------------------------------------- */
void CCirno::Jump() {
	int defaultY = 374;		// �`���m�����ʒu:y��374

	// �`���m�̃W�����v�̍����A�������x�̒��� 
	float jump_speed = 7.0f;	// �W�����v�̏����x
	float jump_accel = -0.15f;	// �W�����v�̉����x


	// �����Ԃ̎�
	if(m_State == Cirno_Run) {
		// �X�y�[�X�L�[�������ꂽ��
		if(CDIKeyBoard::GetKeyPrs( DIK_SPACE )) {
			m_State = Cirno_JumpUp;	// ��Ԃ��W�����v���ɂ���
			m_Vy = jump_speed;			// �����ŃW�����v
		}
	}
	// �W�����v��Ԃ̎�
	else {
		m_Vy += jump_accel;		// �t���[�����ɑ��x�ɉ����x�������Ă���

		// �ϒ��W�����v����
		// �㏸���Ƀ{�^����������牺�~�Ɉڍs
		if((m_Vy > 0) && !CDIKeyBoard::GetKeyPrs( DIK_SPACE )) {
			m_Vy = 0.0f;
		}

		// ���x�����Ȃ�`���m�̏�Ԃ����~���ɂ���
		if(m_Vy < 0) {
			m_State = Cirno_JumpDown;
		}

		// �����ʒu��艺�ɍs���Ȃ��悤�ɂ���
		if(m_Chara.y >= defaultY) {
			m_Chara.y = defaultY;
			m_Vy = 0.0f;
			m_State = Cirno_Run;
		}
	}
	
	m_Chara.y -= (int)m_Vy;			// �`���m�̈ʒu���X�V

	// �����蔻��X�V
	m_hitRect.top = m_Chara.y - 50;
	m_hitRect.bottom = m_Chara.y + 45;

}

/* -------------------------------------------
	�EAnime() :�@�A�j���[�V���������֐�
-------------------------------------------- */
void CCirno::Anime() {
	int frameSpeed = 10;	// �����Ԃ̃`���m�A�j���̃X�s�[�h(�t���[����)

	switch(m_State) {

		/* ----- �����Ԃ̎� ----- */
		case Cirno_Run:
			{
				/* ----- frameSpeed���ɕ\����`��ς��� ----- */
				int i = m_AnimeCount / frameSpeed;

				if(m_lastAnime != i) {
					switch( i ) {
						case 0:
							m_rect.left = 0;
							m_rect.right = 128;
							break;
		
						case 1:
							m_rect.left = 128;
							m_rect.right = 256;
							break;

						case 2:
							m_rect.left = 256;
							m_rect.right = 384;
							break;

						case 3:
							m_rect.left = 384;
							m_rect.right = 512;
							break;
					}
					m_lastAnime = i;
				}
			}		
			m_AnimeCount++;
			if(m_AnimeCount == frameSpeed * 4) {
				m_AnimeCount = 0;
			}
			break;

		/* ----- �W�����v���i�㏸�j�̎� ---- */
		case Cirno_JumpUp:
			m_rect.left = 512;
			m_rect.right = 640;
			break;

		/* ----- �W�����v���i���~�j�̎� ---- */
		case Cirno_JumpDown:
			m_rect.left = 640;
			m_rect.right = 768;
			break;
	}
}
