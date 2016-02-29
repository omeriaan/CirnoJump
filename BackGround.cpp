/* ============================================================
	�EBackGround.cpp
			�w�i�N���X�̏���
============================================================= */

#include "stdafx.h"

#include "BackGround.h"
#include "DxGraphic.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		�R���X�g���N�^
------------------------------------------ */
CBackGround::CBackGround() 
	: m_pVertex( NULL ),
	  m_pTexture( NULL )
{
}

CBackGround::CBackGround(LPDIRECT3DTEXTURE9 tex)
	: m_pVertex( NULL ),
	  m_pTexture( NULL )
{
	InitBackGround( tex );
}

/* -----------------------------------------
		�f�X�g���N�^
------------------------------------------ */
CBackGround::~CBackGround() {
	CleanUp();	// ��������Ăяo��
}

/* -----------------------------------------
	InitBackGround() : �������֐�
------------------------------------------ */
void CBackGround::InitBackGround(LPDIRECT3DTEXTURE9 tex) {

	// �f�t�H���g���_�f�[�^(�w�i�p)
	CUSTOMVERTEX defaultBGVertices[4] = {
		{   0.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
		{ 640.0f,	0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
		{ 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f },
		{	0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f } 
	};


	// ���_�f�[�^�����o�ϐ��Ƀf�t�H���g�l����
	for(int i = 0; i < 4; i++) {
		m_Vertices[i] = DefaultBGVertices[i];
	}

	// �e�N�X�`�������o�ݒ�
	m_pTexture = tex;

	// ���_�o�b�t�@�̍쐬
	if(FAILED(CDxGraphic::m_pD3DDevice->CreateVertexBuffer( sizeof(CUSTOMVERTEX)*4, 0, FVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &m_pVertex, NULL ))) {
		MessageBox(NULL, _T("���_�o�b�t�@�̍쐬�Ɏ��s���܂���"), _T("Error"), MB_OK | MB_ICONSTOP);
	}

	// ���_�o�b�t�@�����b�N�����_�f�[�^���R�s�[����
	void *pData;
	if(SUCCEEDED(m_pVertex->Lock(0, sizeof(CUSTOMVERTEX)*4, (void**)&pData, 0))) {
		memcpy(pData, m_Vertices, sizeof(CUSTOMVERTEX)*4);
		m_pVertex->Unlock();			// ���b�N������
	}
}

/* ------------------------------------------
	CleanUp() : �������
------------------------------------------- */
void CBackGround::CleanUp() {
	SAFE_RELEASE( m_pVertex );	// ���_�o�b�t�@�����
	m_pVertex = NULL;
}

/* -----------------------------------------------------------------------
	ScrollBackGround() : ���_�f�[�^��ς��Ĕw�i���X�N���[��������֐�
		�X�N���[���ɂ̓��b�v�e�N�X�`���A�h���b�V���O���[�h�𗘗p���A
		���t���[�����ƂɃe�N�X�`�����W�����炵�Ă����B
			������: u���̈ړ���
			������: v���̈ړ���
----------------------------------------------------------------------- */
void CBackGround::ScrollBackGround(float moveU, float moveV) {

	// �����e���_��u���W���f�t�H���g���_���W����4.0f���ꂽ�璸�_���f�t�H���g���_���W�ɖ߂�
	if(	abs(DefaultBGVertices[0].tu - m_Vertices[0].tu) >= 4.0f
		&& abs(DefaultBGVertices[1].tu - m_Vertices[1].tu) >= 4.0f
		&& abs(DefaultBGVertices[2].tu - m_Vertices[2].tu) >= 4.0f
		&& abs(DefaultBGVertices[3].tu - m_Vertices[3].tu) >= 4.0f )
	{
		for(int i = 0; i < 4; i++) {
			m_Vertices[i].tu = DefaultBGVertices[i].tu;
		}
	}

	// �����e���_��v���W���f�t�H���g���_���W����4.0f���ꂽ�璸�_���f�t�H���g���_���W�ɖ߂�
	if(	abs(DefaultBGVertices[0].tu - m_Vertices[0].tu) >= 4.0f
		&& abs(DefaultBGVertices[1].tv - m_Vertices[1].tv) >= 4.0f
		&& abs(DefaultBGVertices[2].tv - m_Vertices[2].tv) >= 4.0f
		&& abs(DefaultBGVertices[3].tv - m_Vertices[3].tv) >= 4.0f )
	{
		for(int i = 0; i < 4; i++) {
			m_Vertices[i].tv = DefaultBGVertices[i].tv;
		}
	}

	for(int i = 0; i < 4; i++) {
		m_Vertices[i].tu += moveU;	// �e���_��u�������Ɉړ�
		m_Vertices[i].tv += moveV;	// �e���_��v�������Ɉړ�
	}

	void *pData;
	if(SUCCEEDED(m_pVertex->Lock(0, sizeof(CUSTOMVERTEX)*4, (void**)&pData, 0))) {
		memcpy(pData, m_Vertices, sizeof(CUSTOMVERTEX)*4);
		m_pVertex->Unlock();			// ���b�N������
	}
}


/* -----------------------------------------
	Draw() : �`��֐�
------------------------------------------- */
void CBackGround::Draw() {
	LPDIRECT3DDEVICE9 D3DDevice = CDxGraphic::m_pD3DDevice;
	D3DDevice->SetStreamSource(0, m_pVertex, 0, sizeof(CUSTOMVERTEX) );
	D3DDevice->SetTexture(0, m_pTexture);
	D3DDevice->SetFVF( FVF_CUSTOMVERTEX );
	D3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}