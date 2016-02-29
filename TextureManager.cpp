/* ==========================================================
	�ETextureManager.cpp
			�e�N�X�`���Ǘ��N���X�̏���
============================================================= */

#include "stdafx.h"

#include "TextureManager.h"
#include "DxGraphic.h"
#include "WinMain.h"

#include "Memory_Leak.h"	// �������[���[�N���m�p

// �ÓI�����o������
BYTE* CTextureManager::m_pPointer = NULL;			
map<tstring, LPDIRECT3DTEXTURE9> CTextureManager::m_MapTexture;

// �t�@�C���w�b�_�[�\����
// 128*2 + 4 + 4 = 264 Byte
// Unicode�͔��p�A�S�p���ɂP����2Byte
struct FILEHeader {
	TCHAR	fileName[128];
	DWORD	fileSize;
	DWORD	address;
};

/* -----------------------------------------------------------
	�ECreateTexture() : �e�N�X�`���쐬�֐�
		- dat�t�@�C������e�N�X�`�����쐬����
		- �������}�b�v�h�t�@�C�����g�p
		- �e�N�X�`���̓ǂݍ��݂̓��C�����[�v�O�ɑS�ēǂݍ���
------------------------------------------------------------ */
bool CTextureManager::CreateTexture() {
	vector<FILEHeader> headerArray;

	/* ------------------- dat�t�@�C���ǂݍ��� ------------------------ */

	// dat�t�@�C�����J��
	FILE *fp = _tfopen( DATAFILE , _T("rb"));
	if(fp == NULL) {
		MessageBox(NULL, _T("dat�t�@�C���I�[�v�����s"), _T("Error"), MB_OK | MB_ICONSTOP);	
		return false;
	}

	// dat�t�@�C���ɂ���t�@�C�������擾
	int fileNum = 0;
	fread(&fileNum, sizeof(int), 1, fp);

	for(int i = 0; i < fileNum; i++) {
		fseek(fp, sizeof(int), SEEK_SET);			// dat�t�@�C���擪����4Byte���A�|�C���^�ړ�
		fseek(fp, sizeof(FILEHeader)*i, SEEK_CUR);	// FILEHeader���A�|�C���^�ړ�

		// �t�@�C�������擾
		TCHAR ch[128];
		fread(&ch[0], sizeof(TCHAR[128]), 1, fp);
		tstring fName = tstring( ch );

		// �t�@�C���T�C�Y���擾
		DWORD size;
		fread(&size, sizeof(DWORD), 1, fp);

		// �t�@�C���w�b�_�[��������headerArray�Ɋi�[
		if(size !=0 && fName.end() != find(fName.begin(), fName.end(), _T('.'))) {
			FILEHeader fHeader;
			_tcscpy(fHeader.fileName, ch);
			fHeader.fileSize = size;

			// �t�@�C���A�h���X���擾
			fread(&fHeader.address, sizeof(DWORD), 1, fp);

			back_inserter( headerArray ) = fHeader;
		}
	}

	fclose( fp );	// �t�@�C���ǂݍ��ݏI��


	/* ------------------- �������}�b�v�h�t�@�C�� ------------------------ */
	HANDLE hFile = CreateFile(DATAFILE, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
	if(hFile == INVALID_HANDLE_VALUE) { 
		MessageBox(NULL, _T("CreateFile���s"), _T("Error: �������}�b�v�h�t�@�C��"), MB_OK | MB_ICONSTOP);	
		return false;		
	}

	// �t�@�C���}�b�s���O�I�u�W�F�N�g���쐬
	HANDLE hMap = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, DATAFILE);
	if(hMap <= 0) {	
		MessageBox(NULL, _T("CreateFileMapping���s"), _T("Error: �������}�b�v�h�t�@�C��"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �|�C���^���擾
	m_pPointer = (BYTE*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if(m_pPointer == NULL) {
		MessageBox(NULL, _T("MapViewOfFile���s"), _T("Error: �������}�b�v�h�t�@�C��"), MB_OK | MB_ICONSTOP);
		return false;
	}

	/* ------------------- �e�N�X�`���쐬 ------------------------- */
	for(UINT i = 0; i < headerArray.size(); i++) {
		LPDIRECT3DTEXTURE9 texture;
		BYTE* ptr = m_pPointer + headerArray[i].address;	// dat�t�@�C���̐擪����address���A�|�C���^�ړ�
		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( CDxGraphic::m_pD3DDevice, 
															ptr,
															headerArray[i].fileSize,
															D3DX_DEFAULT_NONPOW2,
															D3DX_DEFAULT_NONPOW2,
															0,
															0,
															D3DFMT_UNKNOWN,
															D3DPOOL_MANAGED,
															D3DX_FILTER_NONE,
															D3DX_DEFAULT,
															0,
															NULL,
															NULL,
															&texture);
		if(FAILED(hr)) {
			return false;
		}

		m_MapTexture.insert( pair<tstring, LPDIRECT3DTEXTURE9>(tstring(headerArray[i].fileName), texture) );		// �}�b�v�Ƀe�N�X�`����}��
	}

	/* -------------------- �u�����N�e�N�X�`���쐬 --------------------- */
	LPDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTexture( CDxGraphic::m_pD3DDevice,
									512,
									512,
									0,
									0,
									D3DFMT_UNKNOWN,
									D3DPOOL_MANAGED,
									&texture);
	if(FAILED(hr)) {
		return false;
	}

	m_MapTexture.insert( pair<tstring, LPDIRECT3DTEXTURE9>(_T("BlankTex"), texture) );		// �}�b�v�Ƀu�����N�e�N�X�`����}��

	return true;
}

/* -------------------------------------------------------
	�EDeleteTexture() : �e�N�X�`���폜�֐�
-------------------------------------------------------- */
void CTextureManager::DeleteTexture() {
	// �쐬�����e�N�X�`�����������
	map<tstring, LPDIRECT3DTEXTURE9>::iterator it = m_MapTexture.begin();
	while( it != m_MapTexture.end() ) {
		SAFE_RELEASE( (*it).second );
		it++;
	}

	m_MapTexture.clear();
	UnmapViewOfFile( m_pPointer );	// �}�b�s���O����
	m_pPointer = NULL;
}

/* -------------------------------------------------------
	�EGetTexture() : �e�N�X�`��getter�֐�
-------------------------------------------------------- */
LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(tstring keyName) {
	map<tstring, LPDIRECT3DTEXTURE9>::iterator it = m_MapTexture.find( keyName );
	if(it == m_MapTexture.end()) {
		MessageBox(NULL, _T("�w�肵���e�N�X�`�������݂��܂���B"), _T("Error: TextureManager"), MB_OK | MB_ICONSTOP);
		PostMessage(GethWnd(), WM_QUIT, 0, 0);	// ���C�����[�v�𔲂��ďI��
		return NULL;
	}
	return it->second;	// �e�N�X�`����Ԃ�
}