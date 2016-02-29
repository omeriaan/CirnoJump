/* ==========================================================
	�EGame.cpp
			�Q�[�����e�̏���
============================================================= */

#include "stdafx.h"

#include "Game.h"
#include "scene.h"
#include "Scene_Title.h"
#include "Scene_GameMain.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

// �ÓI�����o�̏�����
CScene*			CGame::m_pScene			= NULL;
CSceneTitle*	CGame::m_pSceneTitle	= NULL;
CSceneGameMain*	CGame::m_pSceneGameMain = NULL;


/* -----------------------------------------
		�R���X�g���N�^
------------------------------------------ */
CGame::CGame() {
	m_pSceneTitle = new CSceneTitle();
	m_pSceneGameMain = new CSceneGameMain();
	ChangeScene( Scene_TITLE );
}


/* -----------------------------------------
		�f�X�g���N�^
------------------------------------------ */
CGame::~CGame() {
	CleanUp();	// �I�u�W�F�N�g�����
}

/* -----------------------------------------------
	�ECleanUp()		Scene�I�u�W�F�N�g�̉������
------------------------------------------------ */
void CGame::CleanUp() {
	delete m_pSceneTitle;
	m_pSceneTitle = NULL;
	delete m_pSceneGameMain;
	m_pSceneGameMain = NULL;
}

/* --------------------------------------------------
	�EUpDate()
		�V�[���̎��s
-------------------------------------------------- */
void CGame::UpDate() {
	m_pScene->Exec();			// ���݂̃V�[�������s
}

/* --------------------------------------------------
	�EChangeScene()
	�Q�[���V�[����؂�ւ���֐�
-------------------------------------------------- */
void CGame::ChangeScene(Scene scene) {
	// m_pScene��NULL�ł͂Ȃ��ꍇ�A�O�̃V�[����|������
	if(m_pScene != NULL) {
		m_pScene->CleanUp();
	}

	switch( scene ) {
		case Scene_TITLE:
			m_pScene =  m_pSceneTitle;
			break;

		case Scene_GAMEMAIN:
			m_pScene = m_pSceneGameMain;
			break;
	}

	m_pScene->Init();	// ������
}
