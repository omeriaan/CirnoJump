/* ============================================================
	�EScene_GameMain.cpp
			�Q�[�����C���̏���
============================================================= */

#include "stdafx.h"

#include "Scene_GameMain.h"
#include "Game.h"
#include "DxGraphic.h"
#include "DIKeyBoard.h"
#include "BackGround.h"
#include "Cirno.h"
#include "Utsuho.h"
#include "TextureManager.h"

#include "Memory_Leak.h"

/* -----------------------------------------
		�R���X�g���N�^
------------------------------------------ */
CSceneGameMain::CSceneGameMain() 
	: m_pBG_Mountain1( NULL ),
	  m_pBG_Mountain2( NULL ),
	  m_pBG_Sky( NULL ),
	  m_pBG_Clouds( NULL ),
	  m_pBG_Ground( NULL ),
	  m_pCirno( NULL ),
	  m_pUtsuho( NULL )
	{
	}


/* -----------------------------------------
		�f�X�g���N�^
------------------------------------------ */
CSceneGameMain::~CSceneGameMain() {
	CleanUp();
}

/* -----------------------------------------
	�EInit() :�@�������֐�
------------------------------------------ */
void CSceneGameMain::Init() {
	// �w�i�N���X�̃C���X�^���X��

	m_pBG_Mountain1 = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Mountain1.dds") ));
	m_pBG_Mountain2 = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Mountain2.dds") ));
	m_pBG_Sky = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Sky.png") ));
	m_pBG_Clouds = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Clouds.dds") ));
	m_pBG_Ground = new CBackGround( CTextureManager::GetTexture( _T("img\\BG_Ground.dds") ));	

	m_pCirno = new CCirno();	// �`���m�̃C���X�^���X��
	m_pUtsuho = new CUtsuho();	// ����̃C���X�^���X��
}

/* -----------------------------------------
	�ECleanUp() : ��������֐�
------------------------------------------ */
void CSceneGameMain::CleanUp() {

	// �w�i�N���X�̃C���X�^���X�����
	delete m_pBG_Mountain1;
	delete m_pBG_Mountain2;
	delete m_pBG_Sky;
	delete m_pBG_Clouds;
	delete m_pBG_Ground;
	m_pBG_Mountain1 = NULL;
	m_pBG_Mountain2 = NULL;
	m_pBG_Sky		= NULL;
	m_pBG_Clouds	= NULL;
	m_pBG_Ground	= NULL;

	// �C���X�^���X�����
	delete m_pCirno;
	m_pCirno = NULL;
	delete m_pUtsuho;
	m_pUtsuho = NULL;
}

/* -----------------------------------------
	�EExec() : ���s�֐�
------------------------------------------ */
void CSceneGameMain::Exec() {
	// ESC�L�[����������^�C�g���ɖ߂�
	if(CDIKeyBoard::GetKeyPrs( DIK_ESCAPE )) {
		CGame::ChangeScene( Scene_TITLE );
		return;
	}

	/* ----- �w�i�̏��� ----- */
	// �w�i���X�N���[��
	m_pBG_Clouds->ScrollBackGround(0.0006f, 0.0f);		// �_�i��������`�蓮���j
	m_pBG_Mountain1->ScrollBackGround(0.001f, 0.0f);	// ��O�̎R�i���傢���������j
	m_pBG_Mountain2->ScrollBackGround(0.0007f, 0.0f);	// ���̎R�i������蓮���j
	m_pBG_Ground->ScrollBackGround(0.003f, 0.0f);		// �n�ʁi���������j

	// �w�i��`��
	m_pBG_Sky->Draw();			// ��
	m_pBG_Mountain2->Draw();	// �R�i���j
	m_pBG_Mountain1->Draw();	// �R�i��O�j
	m_pBG_Clouds->Draw();		// �_
	m_pBG_Ground->Draw();		// �n��


	/* ----- �`���m�̏��� ----- */
	m_pCirno->Jump();	// �`���m�W�����v����
	m_pCirno->Anime();	// �`���m�A�j������
	m_pCirno->Draw();	// �`���m��`��

	/* ----- ����̏��� ----- */
	m_pUtsuho->Anime();	// �A�j������
	m_pUtsuho->Draw();	// �`��
}
