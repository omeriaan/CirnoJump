/* ============================================================
	�EScene_Title.cpp
			�Q�[���^�C�g����ʂ̏���
============================================================= */

#include "stdafx.h"

#include "WinMain.h"
#include "Game.h"
#include "Scene_Title.h"
#include "DxGraphic.h"
#include "DIKeyBoard.h"
#include "TextureManager.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

/* -----------------------------------------
		�R���X�g���N�^
------------------------------------------ */
CSceneTitle::CSceneTitle() {
	Init();
}

/* -----------------------------------------
		�f�X�g���N�^
------------------------------------------ */
CSceneTitle::~CSceneTitle() {
	CleanUp();
}

/* -----------------------------------------
	�EInit() : �������֐�
------------------------------------------ */
void CSceneTitle::Init() {
	// �J�[�\���̏����ʒu
	m_Cursor.x = 59;
	m_Cursor.y = 294;

	m_isPrsLast = false;	
	m_nowSelect = Start;	// �u�����[�Ɓv�p�l���ɂ��킹��
}

/* -----------------------------------------
	�ECleanUp() : ��������֐�
------------------------------------------ */
void CSceneTitle::CleanUp() {
}

/* -----------------------------------------
	�EExec() : ���s�֐�
------------------------------------------ */
void CSceneTitle::Exec() {
	MoveCursor();	// �J�[�\���ړ�����

	// �����G���^�[�������ꂽ��V�[����ύX
	if(CDIKeyBoard::GetKeyPrs( DIK_RETURN )) {
		switch( m_nowSelect ) {
			case Start:
				CGame::ChangeScene( Scene_GAMEMAIN );
				break;
			
			case Option:
				break;

			case End:
				PostMessage(GethWnd(), WM_QUIT, 0, 0);	// ���C�����[�v�𔲂��ďI��
				break;
		}
		//return;
	}

	Draw();			// �`�揈��
}

/* -----------------------------------------
	�EMoveCursor() : �J�[�\���ړ������֐�
------------------------------------------ */
void CSceneTitle::MoveCursor() { 
	// �e�p�l����y���W
	//�u�����[�Ɓv�p�l��	: y = 294
	//�u���Ղ����v�p�l��	: y = 344
	//�u�����v�p�l��		: y = 394

	if(CDIKeyBoard::GetKeyPrs( DIK_UP ) && !m_isPrsLast) {
		switch( m_nowSelect ) {
			case Start:
				m_nowSelect = End;
				m_Cursor.y = 394;
				break;

			case Option:
				m_nowSelect = Start;
				m_Cursor.y = 294;
				break;

			case End:
				m_nowSelect = Option;
				m_Cursor.y =344;
				break;
		}
	}
	else if(CDIKeyBoard::GetKeyPrs( DIK_DOWN ) && !m_isPrsLast) {
		switch( m_nowSelect ) {
			case Start:
				m_nowSelect = Option;
				m_Cursor.y = 344;
				break;

			case Option:
				m_nowSelect = End;
				m_Cursor.y = 394;
				break;

			case End:
				m_nowSelect = Start;
				m_Cursor.y = 294;
				break;
		}
	}

	if(CDIKeyBoard::GetKeyPrs( DIK_UP ) || CDIKeyBoard::GetKeyPrs( DIK_DOWN )) {
		m_isPrsLast = true;
	}
	else {
		m_isPrsLast = false;
	}
}

/* -------------------------------------------
	�EDraw() :�@�`�揈�������֐�
		�`��̓X�v���C�g���g�p
-------------------------------------------- */
void CSceneTitle::Draw() {
	/* ----- �e�\����`��ݒ� ----- */
	RECT	bg_rc		= {0, 0, 640, 480},
			logo_rc		= {0, 0, 360, 240},
			cirno_rc	= {0, 0, 424, 424},
			start_rc	= {0, 0, 136, 48},
			option_rc	= {0, 0, 136, 48},
			end_rc		= {0, 0, 136, 48},
			cursor_rc	= {0, 0, 64, 64};

	/* ----- �e�\���ʒu��ݒ� ----- */
	D3DXVECTOR3 center(0, 0, 0); 
	D3DXVECTOR3 bg_pos(0, 0, 0),
				logo_pos(10, 50, 0),
				cirno_pos(216, 56, 0),
				start_pos(107, 294, 0),
				option_pos(107, 344, 0),
				end_pos(107, 394, 0),
				cursor_pos((float)m_Cursor.x, (float)m_Cursor.y, 0);		

	CDxGraphic::m_pD3DXSprite->Begin( D3DXSPRITE_ALPHABLEND );
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_BG.png")), &bg_rc, &center, &bg_pos, 0xFFFFFFFF );				// �^�C�g���w�i
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_Cirno.dds")), &cirno_rc, &center, &cirno_pos, 0xFFFFFFFF );		// �`���m
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_Logo.dds")), &logo_rc, &center, &logo_pos, 0xFFFFFFFF );			// �^�C�g�����S
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_StartPanel.dds")), &start_rc, &center, &start_pos, 0xFFFFFFFF );		// �����[�ƃp�l��
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_OptionPanel.dds")), &option_rc, &center, &option_pos, 0xFFFFFFFF );	// ���Ղ����p�l��
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Title_EndPanel.dds")), &end_rc, &center, &end_pos, 0xFFFFFFFF );				// �����p�l��
	CDxGraphic::m_pD3DXSprite->Draw( CTextureManager::GetTexture(_T("img\\Snow_S.dds")), &cursor_rc, &center, &cursor_pos, 0xFFFFFFFF );			// ��J�[�\��

	CDxGraphic::m_pD3DXSprite->End();
}

