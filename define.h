/* ===============================================================
	�Edefine.h
		�J���ɕK�v�ȃ}�N���A�萔���܂Ƃ߂��w�b�_�t�@�C��
================================================================ */

#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <tchar.h>	// TCHAR�^C�W�����C�u����

// tchar�^��string
typedef std::basic_string<TCHAR> tstring;					// tstring�^
typedef std::basic_ostringstream<TCHAR> tostringstream;		// tostringstream�^	
typedef std::basic_istringstream<TCHAR> tistringstream;		// tistringstream�^

/* ----- �}�N�� ----- */
#define SAFE_RELEASE(x) { if(x) x->Release(); }	// Direct3D�J���}�N�� :RELEASE

#endif