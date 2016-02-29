/* ==============================================================================
	�EDx_Graphic.h
		���F���̃N���X�̃����o�͑S��static�Ƃ��A�P�������݂�����̂Ƃ���B
			new�ŃC���X�^���X�����Ȃ��ł��������B
============================================================================== */

#ifndef __DXGRAPHIC_H__
#define __DXGRAPHIC_H__

#include <d3dx9.h>		// Direct3D & D3DX
#include <dxerr.h>

class CDxGraphic {
private:
	static PDIRECT3D9				m_pD3D;				// IDirect3D9�C���^�[�t�F�C�X
	static D3DPRESENT_PARAMETERS	m_D3DPP;			// �g�p����f�B�X�v���C�p�����[�^ :�f�o�C�X�����ݒ肷��\����
	static D3DPRESENT_PARAMETERS	m_D3DPPWindow;		// D3DDevice�̐ݒ�i�E�B���h�E���[�h�p�j
	static D3DPRESENT_PARAMETERS	m_D3DPPFull;		// D3DDevice�̐ݒ�i�t���X�N���[���E���[�h�p�j

	static bool					m_FirstTimeChange;	// �E�B���h�E���[�h�؂�ւ������߂Ă����肷��t���O

public:
	static LPDIRECT3DDEVICE9		m_pD3DDevice;		// DirectX3D�f�o�C�X
	static LPD3DXSPRITE				m_pD3DXSprite;		// �X�v���C�g

	static HRESULT		InitD3D(bool);								// Direct3D�����������֐�
	static void			SetDevice();								// D3D�f�o�C�X�ɐݒ��������֐�
	static void			DXCleanUp();								// Direct3D�J���֐�
	static HRESULT		InitD3DObject();							// �X�v���C�g�̃��Z�b�g
	static HRESULT		CleanupD3DObject();							// �X�v���C�g�̕���
	static void			ResetDevice();								// ���X�g�����f�o�C�X�𕜌�����֐�
	static bool			ChangeDisplayMode(bool, RECT*, int, int);	// �E�B���h�E���[�h�؂�ւ��֐�
};

#endif