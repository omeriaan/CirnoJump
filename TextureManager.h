/* ==========================================================
	�ETextureManager.h
			�e�N�X�`���Ǘ��N���X
============================================================= */

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "stdafx.h"
#include <d3dx9.h>		// Direct3D & D3DX

/* ---------------------------------------------------
	�e�N�X�`���Ǘ��N���X : CTextureManager�N���X
--------------------------------------------------- */
class CTextureManager {
private:
	static BYTE* m_pPointer;								// �������}�b�v�h�t�@�C���|�C���^
	static map<tstring, LPDIRECT3DTEXTURE9> m_MapTexture;	// �e�N�X�`���Ǘ�map

public:
	static bool CreateTexture();						// �e�N�X�`���쐬�֐�
	static void DeleteTexture();						// �e�N�X�`���폜�֐�
	static LPDIRECT3DTEXTURE9 GetTexture(tstring);		// �e�N�X�`��getter
};


#endif