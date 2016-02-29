/* ============================================================
	�EBackGround.h
			�w�i�N���X
============================================================= */

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <d3dx9.h>
struct CUSTOMVERTEX;

class CBackGround {
private:
	IDirect3DVertexBuffer9* m_pVertex;		// ���_�o�b�t�@	
	CUSTOMVERTEX			m_Vertices[4];	// ���_�f�[�^�\����
	LPDIRECT3DTEXTURE9		m_pTexture;		// �w�i�e�N�X�`��

public:
	CBackGround();								// �R���X�g���N�^
	CBackGround( LPDIRECT3DTEXTURE9 );			// �R���X�g���N�^(��������)
	~CBackGround();								// �f�X�g���N�^
	void InitBackGround( LPDIRECT3DTEXTURE9 );	// �������֐�
	void CleanUp();								// �������
	void ScrollBackGround(float, float);		// �w�i�X�N���[���֐�
	void Draw();								// �`��֐�
};

#endif