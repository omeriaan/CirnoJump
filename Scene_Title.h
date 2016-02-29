/* =====================================
		�EScene_Title.h
			�Q�[���^�C�g����ʃN���X
====================================== */

#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "scene.h"

// �I���̎��
enum Select {
	Start,		// �u�����[�Ɓv
	Option,		// �u���Ղ����v
	End			// �u�����v
};

class CSceneTitle : public CScene {
private :
	CHARACTER	m_Cursor;		// �J�[�\���̈ʒu
	Select		m_nowSelect;	// ���݂̑I��
	bool		m_isPrsLast;	// �O�t���[���ɉ������t���O
	
public:
	CSceneTitle();		// �R���X�g���N�^			
	~CSceneTitle();		// �f�X�g���N�^
	void Exec();		// ���s�֐�
	void MoveCursor();	// �J�[�\���ړ������֐�
	void Init();		// �������֐�
	void CleanUp();		// ��������֐�
	void Draw();		// �`��֐�
};

#endif