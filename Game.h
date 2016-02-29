/* ====================================
	�EGame.h
		�Q�[�������N���X
===================================== */

#ifndef __GAME_H__
#define __GAME_H__

/* ----- �v���g�^�C�v�錾 ----- */
class CScene;
class CSceneTitle;
class CSceneGameMain;

enum Scene;			// �V�[���̎�ނ�scene.h�ɋL�q

/* ----- Game�N���X ----- */
class CGame {
private:
	static CScene*			m_pScene;			// Scene�I�u�W�F�N�g

	static CSceneTitle*		m_pSceneTitle;		// �^�C�g���V�[���N���X
	static CSceneGameMain*	m_pSceneGameMain;	// �Q�[�����C���V�[���N���X

public:
	CGame();							// �R���X�g���N�^
	~CGame();							// �f�X�g���N�^
	void CleanUp();						// �I�u�W�F�N�g����֐�
	void UpDate();						// �Q�[���V�[�����X�V���A�V�[�������s����֐�
	static void ChangeScene(Scene);		// �Q�[���V�[����؂�ւ���֐�
};

#endif