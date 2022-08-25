#include "stdafx.h"
#include"../Public/UI_Owl.h"

CUI_Owl::CUI_Owl(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	:CUI(pDevice, pDeviceContext)
{
}

CUI_Owl::CUI_Owl(const CUI_Owl& rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Owl::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CUI_Owl::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		return E_FAIL;
	}

	if (FAILED(SetUp_Texture())) {
		return E_FAIL;
	}

	// UI�� ũ�⸦ ����, ���⼱ �ʱ⿡ ����� Prototype_Component_Texture_Owl_Interaction�� UI�� ������ ���� ���� �� ����/���� ����� �����.
	m_tUIInfo.fCX = 280;
	m_tUIInfo.fCY = 50;
	m_tUIInfo.fX = 1200;
	m_tUIInfo.fY = 800;

	//m_fDistanceToCamera = 300;

	return S_OK;
}

void CUI_Owl::Tick(_double TimeDelta)
{
	CGameInstance* pGameInstnace = GET_INSTANCE(CGameInstance);


	m_pTransformCom->Scaled(_float3(m_tUIInfo.fCX, m_tUIInfo.fCY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_tUIInfo.fX - g_iWinCX * 0.5f, -m_tUIInfo.fY + g_iWinCY * 0.5f, 0.f, 1.f));


	//if (m_bInRange) {
	//	// xŰ�� �����ٸ�
	//	if (pGameInstnace->Key_Down(DIK_X)) {

	//	}
	//}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Owl::LateTick(_double TimeDelta)
{
	if (m_bInRange) {
		if (FAILED(m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_UI, this))) {
			MSG_BOX(L"Failed To CUI_Owl : LateTick : m_pRenderer->Add_RenderGroup");
			return;
		}
	}
}

HRESULT CUI_Owl::Render()
{
	//__super::Render(); -> �̰� �θ��� ����, ���⼭ �˾Ƽ� ó���Ұ�, 3��¥�� �ؽ��ĸ� ����ؼ� ��ġ�Ⱑ �� �׷���.

	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	_float4x4   ViewMatrix;
	XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	_float4x4   ProjMatrixTP;
	XMStoreFloat4x4(&ProjMatrixTP, XMMatrixTranspose(XMLoadFloat4x4(&m_ProjMatrix)));
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
		return E_FAIL;

	// ���� �Ÿ� ���Ϸ� �÷��̾ ������ x��ư�� �����ڳĴ� UI�� ���.
	if (FAILED(m_pTextureCom_OwlInteraction->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;



	// Alpha�� ����
	_float fAlpha = 1.f;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fAlpha", &fAlpha, sizeof(_float))))
		return E_FAIL;



	//apply �ϱ����� ���� �������ϹǷ� begin���� ���ڸ� ������.
	if (FAILED(m_pShaderCom->Begin(23)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CUI_Owl::SetUp_Texture()
{
	if (FAILED(__super::SetUp_Components(L"Com_Texture_OwlInteraction", LEVEL_STATIC, L"Prototype_Component_Texture_InteractionUI", (CComponent**)&m_pTextureCom_OwlInteraction))) {
		MSG_BOX(L"Failed To CUI_Owl : SetUp_Texture : SetUp_Component(Com_Texture_OwlInteraction)");
		return E_FAIL;
	}

	if (FAILED(__super::SetUp_Components(L"Com_Texture_OwlNameBase", LEVEL_STATIC, L"Prototype_Component_Texture_message_box_name", (CComponent**)&m_pTextureCom_OwlNameBase))) {
		MSG_BOX(L"Failed To CUI_Owl : SetUp_Texture : SetUp_Component(Com_Texture_OwlNameBase)");
		return E_FAIL;
	}

	if (FAILED(__super::SetUp_Components(L"Com_Texture_OwlScriptBase", LEVEL_STATIC, L"Prototype_Component_Texture_message_box_context", (CComponent**)&m_pTextureCom_OwlScriptBase))) {
		MSG_BOX(L"Failed To CUI_Owl : SetUp_Texture : SetUp_Component(Com_Texture_OwlScriptBase)");
		return E_FAIL;
	}

	return S_OK;
}

CUI_Owl * CUI_Owl::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	CUI_Owl* pInstance = new CUI_Owl(pDevice, pDeviceContext);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(L"Failed To CUI_Owl : Create : pInstance->NativeConstruct_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CUI_Owl::Clone(void * pArg)
{
	CUI_Owl* pInstance = new CUI_Owl(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(L"Failed To CUI_Owl : Clone : pInstance->NativeConstruct");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CUI_Owl::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom_OwlNameBase);
	Safe_Release(m_pTextureCom_OwlScriptBase);
	Safe_Release(m_pTextureCom_OwlInteraction);
}
