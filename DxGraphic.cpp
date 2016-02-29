/* ============================================================
	�EDx_Graphic.cpp
			DirectX3D9�֘A�̏������s��
============================================================= */

#include "stdafx.h"

#include "DxGraphic.h"
#include "WinMain.h"
#include "Game.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

// �ÓI�����o�̏�����
PDIRECT3D9				CDxGraphic::m_pD3D = NULL;				
D3DPRESENT_PARAMETERS	CDxGraphic::m_D3DPP;
D3DPRESENT_PARAMETERS	CDxGraphic::m_D3DPPWindow;
D3DPRESENT_PARAMETERS	CDxGraphic::m_D3DPPFull;
LPDIRECT3DDEVICE9		CDxGraphic::m_pD3DDevice = NULL;
LPD3DXSPRITE			CDxGraphic::m_pD3DXSprite = NULL;
bool					CDxGraphic::m_FirstTimeChange = true;

/* --------------------------------------------------
			Direct3D�������֐� :InitD3D()
-------------------------------------------------- */
HRESULT CDxGraphic::InitD3D(bool bWindow) {
	D3DDISPLAYMODE	dmode;	//�f�B�X�v���C���[�h

	/* ----- Direct3D�I�u�W�F�N�g�̐��� ----- */
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL) {
		return DXTRACE_ERR(_T("InitDXGraphics Direct3DCreate9"), E_FAIL);
	}

	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode);		// ���݂̃f�B�X�v���C���[�h�f�[�^�擾

	/* ----- D3DPRESENT_PARAMETERS�\����(�E�B���h�E���[�h�p)�̐ݒ� ----- */
	ZeroMemory(&m_D3DPPWindow, sizeof(m_D3DPPWindow));						// 0�N���A�ŏ�����
	m_D3DPPWindow.BackBufferFormat			= D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�i���݂̉�ʃ��[�h���g�p�j
	m_D3DPPWindow.BackBufferWidth			= 0;							// ���h�b�g���ݒ�(0:�Ή��t�����Ă���N���C�A���g�G���A�̃T�C�Y)	
	m_D3DPPWindow.BackBufferHeight			= 0;							// �c�h�b�g���ݒ�(0:�Ή��t�����Ă���N���C�A���g�G���A�̃T�C�Y)
	m_D3DPPWindow.BackBufferCount			= 1;							// �o�b�N�o�b�t�@�̐�
	m_D3DPPWindow.SwapEffect				= D3DSWAPEFFECT_DISCARD;		// �t���b�v�̕��@�i�ʏ�͂��̒萔�ł悢�j
	m_D3DPPWindow.EnableAutoDepthStencil	= TRUE;							// �X�e���V���o�b�t�@�̗L��(TRUE:�L / FALSE:��)
	m_D3DPPWindow.AutoDepthStencilFormat	= D3DFMT_D16;					// �X�e���V���t�H�[�}�b�g
	m_D3DPPWindow.Windowed					= TRUE;							// �E�B���h�E���[�h�̐ݒ�

	/* ----- D3DPRESENT_PARAMETERS�\����(�t���X�N���[�����[�h�p)�̐ݒ� ----- */
	ZeroMemory(&m_D3DPPFull, sizeof(m_D3DPPFull));						// 0�N���A�ŏ�����
	m_D3DPPFull.BackBufferFormat		= D3DFMT_X8R8G8B8;				// �o�b�N�o�b�t�@�t�H�[�}�b�g
	m_D3DPPFull.BackBufferWidth			= SIZEFULL_WIDTH;				// ���h�b�g���ݒ�	
	m_D3DPPFull.BackBufferHeight		= SIZEFULL_HEIGHT;				// �c�h�b�g���ݒ�
	m_D3DPPFull.BackBufferCount			= 1;							// �o�b�N�o�b�t�@�̐�
	m_D3DPPFull.SwapEffect				= D3DSWAPEFFECT_DISCARD;		// �t���b�v�̕��@�i�ʏ�͂��̒萔�ł悢�j
	m_D3DPPFull.EnableAutoDepthStencil	= TRUE;							// �X�e���V���o�b�t�@�̗L��(TRUE:�L / FALSE:��)
	m_D3DPPFull.AutoDepthStencilFormat	= D3DFMT_D16;					// �X�e���V���t�H�[�}�b�g
	m_D3DPPFull.Windowed				= FALSE;						// �E�B���h�E���[�h�̐ݒ�
	

	/* ----- �f�o�C�X�I�u�W�F�N�g�̐��� ----- */
	if( bWindow ) {
		m_D3DPP = m_D3DPPWindow;
	}
	else {
		m_D3DPP = m_D3DPPFull;
	}

	// �uHAL&�n�[�h�E�F�A���_�����v�f�o�C�X�𐶐�
	HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GethWnd(), 
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPP, &m_pD3DDevice);
	if( FAILED(hr) ) {	// ���������Ɏ��s������
		// �uHAL&�\�t�g�E�F�A���_�����v�f�o�C�X�𐶐�
		hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GethWnd(), 
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPP, &m_pD3DDevice);
		if( FAILED(hr) ) {	// ���������Ɏ��s������
			// �uREF&�\�t�g�E�F�A���_�����v�f�o�C�X���쐬
			hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GethWnd(), 
							D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPP, &m_pD3DDevice);
			if( FAILED(hr) ) {	// �ǂ̃f�o�C�X���擾�ł��Ȃ�������
				return DXTRACE_ERR(_T("InitDXGraphics CreateDevice"), hr);
			}
		}
	}

	/* ----- �X�v���C�g�̏����� ----- */
	hr = D3DXCreateSprite(m_pD3DDevice, &m_pD3DXSprite);				// �X�v���C�g�쐬
	if( FAILED(hr) ) {
		return DXTRACE_ERR(_T("InitDXGraphics D3DXCreateSprite"), hr);
	}

	SetDevice();	// D3DDevice�ɐݒ��������

	return S_OK;
}	

/* ----------------------------------------------------------
	�ESetDevice() : D3DDevice�ɐݒ��������֐�
----------------------------------------------------------- */
void CDxGraphic::SetDevice() {

	/* ----- �|���S���̃A���t�@�u�����f�B���O�̐ݒ� ----- */
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );					// �A���t�@�u�����h��L���ɂ���
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND         , D3DBLEND_SRCALPHA );		// �`�挳�̃A���t�@�u�����f�B���O�ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND        , D3DBLEND_INVSRCALPHA );	// �`���̃A���t�@�u�����f�B���O�ݒ�

	/* ----- ���`�⊮�ɂ��|���S���̃W���M�[�������� ----- */
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	/* ----- ���b�v�e�N�X�`���A�h���b�V���O���[�h��ݒ�@----- */
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );		// u���Ƀ��b�v
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );		// v���Ƀ��b�v
}


/* ----------------------------------------------------------
			Dirext3D�J���֐� :DXCleanUp()
---------------------------------------------------------- */
void CDxGraphic::DXCleanUp() {
	SAFE_RELEASE( m_pD3DXSprite );		// �X�v���C�g�̉��
	m_pD3DXSprite = NULL;
	SAFE_RELEASE( m_pD3DDevice );		// �f�o�C�X�I�u�W�F�N�g�̉��
	m_pD3DDevice = NULL;
	SAFE_RELEASE( m_pD3D );				// DirectX9�I�u�W�F�N�g�̉��
	m_pD3D = NULL;
}


/* ----------------------------------------------------------------------------------
	D3D�ɊǗ�����Ȃ��I�u�W�F�N�g�̏�����(�X�v���C�g�̃��Z�b�g��) :InitD3DObject()
---------------------------------------------------------------------------------- */
HRESULT CDxGraphic::InitD3DObject() {
	// �X�v���C�g�̏���
	if(m_pD3DXSprite) {
		m_pD3DXSprite->OnResetDevice();
	}

	return S_OK;
}

/* ----------------------------------------------------------------------------------
	D3D�ɊǗ�����Ȃ��I�u�W�F�N�g�̏I������(�X�v���C�g�̕�����) :CleanupD3DObject()
---------------------------------------------------------------------------------- */
HRESULT CDxGraphic::CleanupD3DObject() {
	// �X�v���C�g�̏���
	if(m_pD3DXSprite) {
		m_pD3DXSprite->OnLostDevice();
	}

	return S_OK;
}



/* ----------------------------------------------------------
		���X�g�����f�o�C�X�𕜌�����֐� :ResetDevice()
---------------------------------------------------------- */
void CDxGraphic::ResetDevice() {
	HRESULT hr;
	Sleep(100);										// 0.1�b�҂�

	hr = m_pD3DDevice->TestCooperativeLevel();		// �f�o�C�X��Ԃ̃`�F�b�N	
	if(FAILED(hr)) {
		if(hr == D3DERR_DEVICENOTRESET) {			// �������Z�b�g�\�ȏ�ԂȂ畜�������J�n
			CleanupD3DObject();						// ���\�[�X�����

			hr = m_pD3DDevice->Reset(&m_D3DPP);		// �f�o�C�X�𕜌�
			if(FAILED(hr)){
				if(hr != D3DERR_DEVICELOST) {
					DXTRACE_ERR(_T("ChangeDisplayMode Reset"), hr);
					return;
				}
			}

			InitD3DObject();						// ����������\�[�X���č\�z
		}
	}
}


/* -----------------------------------------------------------------------------
	�E�B���h�E���[�h<-->�t���X�N���[�����[�h�؂�ւ��֐� :ChangeDisplayMode()
----------------------------------------------------------------------------- */
bool CDxGraphic::ChangeDisplayMode(bool bWindow, RECT* rectWindow, int InitWndPosX, int InitWndPosY) {

	if( !bWindow ) {							// �t���X�N���[�� -> �E�B���h�E�̏ꍇ
		m_D3DPP = m_D3DPPWindow;				// �f�o�C�X�p�����[�^���E�B���h�E���[�h�p�ɍ����ւ�
	}
	else {										// �E�B���h�E -> �t���X�N���[���̏ꍇ
		m_D3DPP = m_D3DPPFull;					// �f�o�C�X�p�����[�^���t���X�N���[�����[�h�p�ɍ����ւ�
		GetWindowRect(GethWnd(), rectWindow);	// �E�B���h�E���[�h�̍Ō�̈ʒu�A�T�C�Y���擾	
	}
	
	CleanupD3DObject();									// ���\�[�X�����
	HRESULT hr = m_pD3DDevice->Reset(&m_D3DPP);			// �f�o�C�X�𕜌�
	if(FAILED(hr)) {
		if(hr == D3DERR_DEVICELOST) {
			MessageBox(NULL, _T("DEVICELOST"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == D3DERR_DRIVERINTERNALERROR){
			MessageBox(NULL, _T("DRIVERINTERNALERROR"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == D3DERR_INVALIDCALL) {
			MessageBox(NULL, _T("INVALIDCALL"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == D3DERR_OUTOFVIDEOMEMORY) {
			MessageBox(NULL, _T("OUTOFVIDEOMEMORY"), _T("DeviceLostError"), MB_OK);
		}
		else if(hr == E_OUTOFMEMORY) {
			MessageBox(NULL, _T("OUROFMEMORY"), _T("DeviceLostError"), MB_OK);
		}

		DXTRACE_ERR(_T("ChangeDisplayMode Reset"), hr);
		return false;							// �f�o�C�X�̕����Ɏ��s
	}

	InitD3DObject();					// ����������\�[�X���č\�z

	if( !bWindow ) {					// �t���X�N���[�� -> �E�B���h�E�̏ꍇ
		RECT rect;
		rect.left	= rectWindow->left;
		rect.top	= rectWindow->top;
		if( m_FirstTimeChange ) {					// ���������E�B���h�E���[�h���t���X�N���[���̎�
			rect.left	= InitWndPosX;				// �E�B���h�E�̔z�u�ʒu���f�B�X�v���C�̒����ɂ���
			rect.top	= InitWndPosY;	
		}

		SetWindowLong(GethWnd(), GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE);
		SetWindowPos(GethWnd(), HWND_TOP,
			rect.left, rect.top,
			rectWindow->right - rectWindow->left,
			rectWindow->bottom -rectWindow->top,
			SWP_SHOWWINDOW);
	}
	else {											// �E�B���h�E -> �t���X�N���[���̏ꍇ
		SetWindowLong(GethWnd(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}

	SetDevice();	// ��������D3DDevice�ɐݒ��������

	m_FirstTimeChange = false;						// ���ł�ChangeDisplayMode�����s������false�ɂ���

	return true;
}

