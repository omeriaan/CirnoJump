/* ===============================================================
	�Edefine_game.h
		���̃Q�[���Ɋւ���}�N���A�萔���܂Ƃ߂��w�b�_�t�@�C��
================================================================ */

#ifndef __DEFINE_GAME_H__
#define __DEFINE_GAME_H__

#include <d3d9.h>

/* ----- �萔 ----- */
#define		NAME				 _T("GameWin")		// �E�B���h�E�N���X�p������i�E�B���h�E���j
#define		TITLE				 _T("���邶���")	// �E�B���h�E�N���X�p������i�E�B���h�E�̃^�C�g���j
#define		SIZEWINDOW_WIDTH	 640				// �E�B���h�E���[�h�̉𑜓x�i���j
#define		SIZEWINDOW_HEIGHT	 480				// �E�B���h�E���[�h�̉𑜓x�i�����j
#define		SIZEFULL_WIDTH		 640				// �t���X�N���[�����[�h�̉𑜓x�i���j
#define		SIZEFULL_HEIGHT		 480				// �t���X�N���[�����[�h�̉𑜓x�i����)
#define		DATAFILE			_T("cirjum.dat")	// dat�t�@�C����

/* ----- FPSControl ----- */
const int	REQUEST_FPS	= 60;						// FPS���z�l
const bool	IS_FRAMESKIP = false;					// �t���[���X�L�b�v�̗L��(true:�L false:��)

/* ----- 2�������_�\���� ----- */
struct CUSTOMVERTEX {
	float x, y, z;			// ���_���W
	float rhw;				// ���Z���A �ʏ��1.0f
	DWORD dwColor;			// ���_�̐F
	float tu, tv;			// �e�N�X�`�����W
};
#define FVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/* ----- �f�t�H���g���_�f�[�^(�w�i�p) ----- */
const CUSTOMVERTEX DefaultBGVertices[4] = {
	{   0.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
	{ 640.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
	{ 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f },
	{	0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f } 
};

/* ----- �L�����N�^�[�\���� ----- */
struct CHARACTER {
	int x;	// �L�����N�^�[�ʒu��x���W
	int y;	// �L�����N�^�[�ʒu��y���W
};

/* ----- �����蔻������ ----- */
const bool IS_HITAREAVISIBLE = true;

#endif

