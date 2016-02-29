/* =============================================================
	�EWinMain.cpp
			�E�B���h�E�̏������A���C���֐�������
============================================================== */

#include "stdafx.h"

#include "DxGraphic.h"
#include "DIKeyboard.h"
#include "FPSControl.h"
#include "TextureManager.h"
#include "Game.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

/* ----- �O���[�o���ϐ��錾 ----- */
HWND		hWnd;			 // �E�B���h�E�n���h��
HINSTANCE	g_hInstance;	 // �E�B���h�E�C���X�^���X

bool		g_bWindow			= true;				// �E�B���h�E���[�h�̎w��iTRUE:�E�B���h�E���[�h / FALSE:�t���X�N���[���j
bool		g_bActive			= false;			// �A�N�e�B�u��ԃt���O(TRUE:�A�N�e�B�u��� / FALSE:��A�N�e�B�u���)
bool		g_bDeviceLost		= false;			// �f�o�C�X���X�g�t���O(TRUE:�f�o�C�X���X�g��� / FALSE:��f�o�C�X���X�g���)
RECT		g_rectWindow;							// �E�B���h�E���[�h�ł̍Ō�̈ʒu�A�T�C�Y
int			g_InitWndPosX;							// �E�B���h�E�̏����ʒuX���W�i�f�B�X�v���C�̒����j 
int			g_InitWndPosY;							// �E�B���h�E�̏����ʒuY���W�i�f�B�X�v���C�̒����j

CGame*		 g_pGame			= NULL;				// Game�I�u�W�F�N�g
CFpsControl* g_pFPSController	= NULL;				// FPS�Ǘ��I�u�W�F�N�g

/* ----- �v���g�^�C�v�錾 ----- */
LRESULT		CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// �E�B���h�E�v���V�[�W��
bool		InitApp(HINSTANCE);								// �E�B���h�E�쐬�֐�
void		CleanUp();										// �I�����̉������	

/* ------ getter�֐� ------ */
HWND		GethWnd()	   { return hWnd; }			// �E�B���h�E�n���h��getter
HINSTANCE	GethInstance() { return g_hInstance; }	// �E�B���h�E�C���X�^���Xgetter


/* -------------------------------------
			���C���֐�
-------------------------------------- */
int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszArgs, int nWinMode) {
	// ���������[�N�����o�B�i�f�o�b�O���[�h�̂݁j
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	

	g_hInstance = hInst;
	MSG msg;	// ���b�Z�[�W�\���̕ϐ�


	// �\������E�B���h�E�̒�`�A�o�^�A�\��
	// ����InitApp�֐��̖߂�l��0�Ȃ�A�G���[�l��߂�l�Ƃ��ă��C���֐����I������
	if (!InitApp(hInst)) {	// InitApp�֐����Ăяo���A
		MessageBox(NULL, _T("�A�v���P�[�V�����̏������Ɏ��s���܂���"), _T("Error"), MB_OK | MB_ICONSTOP);
		return false;			// ����ɏI������Ύ��Ƀ��b�Z�[�W���[�v��
	}

	// DirectX9�̏�����
	if( FAILED(CDxGraphic::InitD3D(g_bWindow)) ) {
		MessageBox(NULL, _T("DirectX9�f�o�C�X�̏������Ɏ��s"), _T("Error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// DirectInput8�̏�����
	if( FAILED(CDIKeyBoard::InitDID()) ) {
		MessageBox(NULL, _T("DirectInput8�f�o�C�X�̏������Ɏ��s"), _T("Error"), MB_OK | MB_ICONSTOP);
		CleanUp();
		return false;
	}

	// �e�N�X�`�����쐬
	if( !CTextureManager::CreateTexture() ) {
		MessageBox(NULL, _T("�e�N�X�`���̍쐬�Ɏ��s"), _T("Error"), MB_OK | MB_ICONSTOP);
		CleanUp();
		return false;
	}

	// Game�I�u�W�F�N�g�쐬
	g_pGame = new CGame();
	// FPS�Ǘ��I�u�W�F�N�g�쐬
	g_pFPSController = new CFpsControl();
	g_pFPSController->InitFPS();

	LPDIRECT3DDEVICE9 D3DDevice = CDxGraphic::m_pD3DDevice;		// DxGraphic�f�o�C�X���擾

	// ���C�����[�v
	while( true ) {
		// ���b�Z�[�W�����邩�m�F����
		if( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) ) {
			if( !GetMessage(&msg, NULL, 0, 0) )	break;	// ���b�Z�[�W��WM_QUIT�������烋�[�v�𔲂���
			TranslateMessage(&msg);						// �L�[�{�[�h���p���\�ɂ��邽�߂ɕK�v
			DispatchMessage(&msg);						// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}
		else {
			if( g_bActive ){		// �A�N�e�B�u��Ԃ̎�

				if( g_bDeviceLost ) {				// �f�o�C�X���X�g��Ԃ̎�
					CDxGraphic::ResetDevice();		// �f�o�C�X�𕜌�����
					g_bDeviceLost = false;			// �f�o�C�X���X�g�t���O��false
				}

				CDIKeyBoard::UpDate();				// �L�[�{�[�h���Ď�

				D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );	// �V�[���̃N���A(��)
				D3DDevice->BeginScene();															// �V�[���`��J�n
				g_pGame->UpDate();																	// �V�[���̕`��
				D3DDevice->EndScene();																// �V�[���`��I��

				g_pFPSController->ControlFPS();														// FPS�Ǘ�
				
				if(g_pFPSController->GetDrawFrag()) {
					/* ----- �f�o�b�O���[�h�̎��AFPS�ƃX�L�b�v���[�g��\�� ------ */			
					#ifdef _DEBUG
						tostringstream os;
						os << TITLE 
							<< " - FPS = " << g_pFPSController->GetFPS() << _T(",")
							<< "SkipRate = " << g_pFPSController->GetSkipRate() << _T("\n");
						SetWindowText(hWnd, os.str().c_str());
					#endif

					HRESULT hr = D3DDevice->Present( NULL, NULL, NULL, NULL );	// �V�[���̕\��
					if(hr == D3DERR_DEVICELOST) {								// �����f�o�C�X�����X�g���Ă�����
						g_bDeviceLost = true;									// �f�o�C�X���X�g�t���O��true
					}
				}

				Sleep(1);
			}
			else {					// ��A�N�e�B�u��Ԃ̎�
				WaitMessage();		// ���b�Z�[�W������܂Ń��[�v���ꎞ��~
			}
		}
	}
	
	CleanUp();					// �������
	return msg.wParam;
}

/* ----------------------------------------------------------
	�I�����̉������	
----------------------------------------------------------- */
void CleanUp() {
	delete g_pGame;						// Game�I�u�W�F�N�g�����
	delete g_pFPSController;			// FPS�Ǘ��I�u�W�F�N�g�����
	CTextureManager::DeleteTexture();	// �e�N�X�`�����폜
	CDxGraphic::DXCleanUp();			// DxGraphi�����
	CDIKeyBoard::CleanUp();				// DIKeyboard�����
}

/* ----------------------------------------------------------
	�E�B���h�E�v���V�[�W���֐��iWindowProcedure�j:WndProc()
	���b�Z�[�W�������s��
---------------------------------------------------------- */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_ACTIVATE:								// �A�N�e�B�u��Ԃ��ω�������
			g_bActive = (LOWORD(wParam) != 0);			// �A�N�e�B�u��ԃt���O��ύX
			break;

		case WM_SYSKEYDOWN:								// �V�X�e���L�[�iAlt�L�[�j�������ꂽ��
			switch( wParam ) {
				case VK_RETURN:							// Alt + Enter�������ꂽ��
					// �E�B���h�E���[�h <--> �t���X�N���[���̐؂�ւ�
					bool hr = CDxGraphic::ChangeDisplayMode(g_bWindow, 
															&g_rectWindow,
															g_InitWndPosX,
															g_InitWndPosY	);

					if(!hr) {
						g_bDeviceLost = true;
					}
					else {
						g_bWindow = !g_bWindow;						// �t���O�𔽓]
					}
					break;
			}
			break;

		case WM_SYSCOMMAND:								// �V�X�e���R�}���h���b�Z�[�W(�E�B���h�E�E��̍ŏ����A�ő剻��)��������
			switch( wParam ) {
				case SC_MAXIMIZE:						// �ő剻�{�^�����N���b�N�������C�t���X�N���[�����[�h�ɐ؂�ւ�
					bool hr = CDxGraphic::ChangeDisplayMode(g_bWindow, 
															&g_rectWindow,
															g_InitWndPosX,
															g_InitWndPosY );
					if(!hr) {
						g_bDeviceLost = true;
					}
					else {
						g_bWindow = !g_bWindow;			// �t���O�𔽓]
					}
					break;
			}
			break;

		case WM_DESTROY:								// ����{�^�����N���b�N������
			PostQuitMessage(0);							// WM_QUIT���b�Z�[�W�𔭍s
			break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);	// �f�t�H���g����
}


/* --------------------------------------------------
	InitApp()
	�\������E�B���h�E�̒�`�A�o�^�A�\��
	�߂�l:����I���̂Ƃ��P�A�ُ�I���̎��O
-------------------------------------------------- */
bool InitApp(HINSTANCE hInst) {
	WNDCLASSEX wc;			//�E�B���h�E�N���X�\����

	// �E�B���h�E�N���X���`����
	wc.cbSize			= sizeof(WNDCLASSEX);		// WNDCLASSEX�\���̂̃T�C�Y��ݒ�
	wc.style			= NULL;						// �E�B���h�E�X�^�C��
	wc.lpfnWndProc		= WndProc;					// �E�B���h�E�֐�
	wc.cbClsExtra		= 0;						// �ʏ�͎g��Ȃ��i0�ɂ��Ă����j
	wc.cbWndExtra		= 0;						// �ʏ�͎g��Ȃ��i0�ɂ��Ă����j
	wc.hInstance		= hInst;					// ���̃C���X�^���X�ւ̃n���h��
	wc.hIcon			= NULL;						// ���[�W�A�C�R���i�Ȃ��j
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// �J�[�\���X�^�C��
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	// �E�B���h�E�̔w�i�i���j
	wc.lpszMenuName		= NULL;						// ���j���[�i�Ȃ��j
	wc.lpszClassName	= NAME;						// �E�B���h�E�N���X��
	wc.hIconSm			= NULL;						// �X���[���A�C�R���i�Ȃ��j

	// �E�B���h�E�N���X�̓o�^
	if (!RegisterClassEx(&wc)) {
		return (FALSE);
	}

	// �E�B���h�E�S�̂̃T�C�Y��ݒ肷��
	SetRect(&g_rectWindow, 0, 0, SIZEWINDOW_WIDTH, SIZEWINDOW_HEIGHT);
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, FALSE);
	g_rectWindow.right	= g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom = g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top	= 0;
	g_rectWindow.left	= 0;

	// �E�B���h�E�쐬�ʒu���v�Z����i�f�B�X�v���C�̒����ɔz�u�j
	g_InitWndPosX = (GetSystemMetrics( SM_CXSCREEN ) - SIZEWINDOW_WIDTH) / 2;
	g_InitWndPosY = (GetSystemMetrics( SM_CYSCREEN ) - SIZEWINDOW_HEIGHT) / 2;

	RECT rect;										// top,left : �ʒu / right : �E�B���h�E�̕� / bottom : �E�B���h�E�̍���
	if( g_bWindow ) {								// �E�B���h�E���[�h�̈ʒu�ƃT�C�Y�ݒ�
		rect.top	= g_InitWndPosY;
		rect.left	= g_InitWndPosX;
		rect.right	= g_rectWindow.right;
		rect.bottom = g_rectWindow.bottom;
	}
	else {											// �t���X�N���[�����[�h�̈ʒu�ƃT�C�Y�ݒ�
		rect.top	= 0;
		rect.left	= 0;
		rect.right	= SIZEFULL_WIDTH;
		rect.bottom = SIZEFULL_HEIGHT;
	}

	/* ----- �E�B���h�E�𐶐� ----- */
	hWnd = CreateWindow(
		NAME,									// �E�B���h�E�N���X�̖��O
		TITLE,									// �E�B���h�E�^�C�g��
		g_bWindow ? WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME : WS_POPUP,	// �E�B���h�E�X�^�C��
		rect.left,									// �E�B���h�E�̍����w���W
		rect.top,									// �E�B���h�E�̍����x���W
		rect.right,									// �E�B���h�E�̕�
		rect.bottom,								// �E�B���h�E�̍���
		NULL,										// �e�E�B���h�E�i�Ȃ��j
		NULL,										// ���j���[�i�Ȃ��j
		hInst,										// ���̃v���O�����̃C���X�^���X�̃n���h��
		NULL										// �ǉ������i�Ȃ��j
	);

	/* ----- �E�B���h�E�\�� ----- */
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return true;
}



