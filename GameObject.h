/* ============================================================
	�EGameObject.h
			�Q�[���I�u�W�F�N�g�̃X�[�p�[�N���X
============================================================= */

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CGameObject {
protected:
	CHARACTER	m_Chara;		// �L�����N�^�[���W�ʒu�ʒu
	RECT		m_rectSize;		// ��`�T�C�Y
	RECT		m_rect;			// �\������e�N�X�`����`
	D3DXVECTOR3 m_center;		// ��`�̒��S���W
	tstring		m_textureName;	// �\������e�N�X�`����
	RECT		m_hitRect;		// �����蔻���`
		
public:
	CGameObject() {};		// �R���X�g���N�^	
	~CGameObject() {};		// �f�X�g���N�^

	void Draw();			// �`��֐�
};

#endif