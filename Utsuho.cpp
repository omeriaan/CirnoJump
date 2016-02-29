/* ============================================================
	�EUtsuho.cpp
			����̏���
============================================================= */
#include "stdafx.h"

#include "DxGraphic.h"
#include "TextureManager.h"
#include "Utsuho.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		�R���X�g���N�^
------------------------------------------ */
CUtsuho::CUtsuho() 
{	
	Init();	// ����������
}

/* -----------------------------------------
		�f�X�g���N�^
------------------------------------------ */
CUtsuho::~CUtsuho() {
}

/* -----------------------------------------
	�EInit() :�@�������֐�
------------------------------------------ */
void CUtsuho::Init() {
	
	/* ----- ����̏����ݒ� ----- */
	m_Chara.x = 552;		// ����x���W�ʒu				
	m_Chara.y = 350;		// ����y���W�ʒu

	m_AnimeCount = 0;		// �A�j���[�V�����J�E���g������
	m_lastAnime = 0;		// �O�t���[���̃A�j���̏��

	m_textureName = _T("img\\Utsuho.dds");	// �e�N�X�`����

	/* ----- Draw�ݒ� ----- */
	RECT rc = {0, 0, 176, 176};
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
	�EAnime() :�@�A�j���[�V���������֐�
-------------------------------------------- */
void CUtsuho::Anime() {
	int frameSpeed = 10;	// �A�j���̃X�s�[�h(�t���[����)

	int i = m_AnimeCount / frameSpeed;

	if(m_lastAnime != i) {
		switch( i ) {
			case 0:
				m_rect.left = 0;
				m_rect.right = 176;
				break;

			case 1:
				m_rect.left = 176;
				m_rect.right = 352;
				break;
		}
		m_lastAnime = i;
	}

	m_AnimeCount++;
	if(m_AnimeCount == frameSpeed * 2) {
		m_AnimeCount = 0;	
	}
}
