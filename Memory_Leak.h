// �������[���[�N���m�p�w�b�_�t�@�C��
// ������e�\�[�X�t�@�C��(.cpp)�̃w�b�_�C���N�[�h�̖����ŃC���N���[�h���邱�Ƃ�
// ���������[�N�̌����ӏ�����肷�邱�Ƃ��ł��܂��B

// �֐� _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) �����C���֐��̐擪�ŌĂяo�����ƂŃ������[���[�N�����m���܂��B
// �������[���[�N�̓f�o�b�O���[�h�̂݋@�\���܂��B
// ���������[�N�����ӏ��̓f�o�b�O���[�h�̏o�͂ɕ\������܂��B

#ifndef __MEMORY_LEAK_H__
#define __MEMORY_LEAK_H__

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// �������[���[�N�ӏ����N�����Ă���t�@�C�����A�s����\��
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif