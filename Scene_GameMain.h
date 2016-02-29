/* ===================================
		�EScene_GameMain.h
			�Q�[�����C���N���X
==================================== */

#ifndef __SCENE_GAMEMAIN_H__
#define __SCENE_GAMEMAIN_H__

#include "scene.h"
#include <d3dx9.h>
class CBackGround;
class CCirno;
class CUtsuho;

class CSceneGameMain : public CScene {
private:
	// �w�i�N���X
	CBackGround*	m_pBG_Mountain1;
	CBackGround*	m_pBG_Mountain2;
	CBackGround*	m_pBG_Sky;
	CBackGround*	m_pBG_Clouds;
	CBackGround*	m_pBG_Ground;

	CCirno*	m_pCirno;	// �`���m
	CUtsuho* m_pUtsuho;	// ����


public:
	CSceneGameMain();		// �R���X�g���N�^
	~CSceneGameMain();		// �f�X�g���N�^
	void Init();			// �������֐�
	void Exec();			// ���s�֐�
	void CleanUp();			// ��������֐�
};

#endif