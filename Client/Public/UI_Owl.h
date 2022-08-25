#pragma once

#include "Client_Defines.h"
#include "UI.h"
#include "GameInstance.h"

BEGIN(Client)

class CUI_Owl final : public CUI
{
private:
	CUI_Owl(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CUI_Owl(const CUI_Owl& rhs);
	virtual ~CUI_Owl() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture* m_pTextureCom_OwlNameBase = nullptr;
	CTexture* m_pTextureCom_OwlScriptBase = nullptr;
	CTexture* m_pTextureCom_OwlInteraction = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

	HRESULT SetUp_Texture();

public:
	void Set_InRange(_bool bInRange) { m_bInRange = bInRange; }

private:
	_bool m_bInteractWithPlayer = false;	// �÷��̾�� ��ȣ�ۿ��� �ϴ����� ���� ����, Ư�� Ű�� ���� Ȱ��ȭ�ȴ�.
	_bool m_bInRange = false;				// �÷��̾���� �Ÿ��� ���� ������ ��� true �ƴҰ�� false�̴�.
	_float m_fDistance = 0.f;				// �÷��̾�

public:
	static CUI_Owl* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END