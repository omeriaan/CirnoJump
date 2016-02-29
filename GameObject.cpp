/* ============================================================
	�EGameObject.cpp
			�Q�[���I�u�W�F�N�g�̃X�[�p�[�N���X
============================================================= */
#include "stdafx.h"

#include "DxGraphic.h"
#include "TextureManager.h"
#include "GameObject.h"

#include "Memory_Leak.h"


/* -------------------------------------------
	�EDraw() :�@�`�揈�������֐�
		�`��̓X�v���C�g���g�p
-------------------------------------------- */
void CGameObject::Draw() {
	D3DXVECTOR3 position((float)m_Chara.x, (float)m_Chara.y, 0);

	CDxGraphic::m_pD3DXSprite->Begin( D3DXSPRITE_ALPHABLEND );
	CDxGraphic::m_pD3DXSprite->Draw(CTextureManager::GetTexture(m_textureName.c_str()), &m_rect, &m_center, &position, 0xFFFFFFFF);
	// �����蔻������[�h��ON�Ȃ��������
	if(IS_HITAREAVISIBLE == true) {
		D3DXVECTOR3 hitCenter((float)(m_hitRect.right-m_hitRect.left)/2, (float)(m_hitRect.bottom-m_hitRect.top)/2, 0);
		CDxGraphic::m_pD3DXSprite->Draw(CTextureManager::GetTexture(_T("img\\HitArea.png")), &m_hitRect, &hitCenter, &position, 0xFFFFFFFF);
	}
	CDxGraphic::m_pD3DXSprite->End();
}