/* ===============================================================
	�Escene.h
		�Q�[���J�ڊ֘A�̃C���^�[�t�F�C�X�N���X(���ۃN���X)
		& Scene�Q�b�^�[�֐�
================================================================ */

#ifndef __SCENE_H__
#define __SCENE_H__

// �Q�[���V�[���̎��
enum Scene { 
	Scene_TITLE,
	Scene_GAMEMAIN 
};

class CScene {
public:	
	virtual	~CScene() {}			// ���z�f�X�g���N�^
	virtual void Exec() = 0;		// ���s�֐� :�������z�֐�(�K���I�[�o�[���C�h�����֐� : ���ۃ��\�b�h)
	virtual	void Init() = 0;		// �������֐�
	virtual void CleanUp() = 0;		// ��������֐�
};

#endif