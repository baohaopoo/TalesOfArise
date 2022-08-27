#include "stdafx.h"
#include "..\Public\Level_FireAvatar.h"
#include "GameInstance.h"

CLevel_FireAvatar::CLevel_FireAvatar(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
	, m_pBattle_Manager(CBattle_Manager::GetInstance())
{
	Safe_AddRef(m_pBattle_Manager);
}

HRESULT CLevel_FireAvatar::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	//if (FAILED(Ready_Lights()))
	//	return E_FAIL;

	//if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
	//	return E_FAIL;

	if (FAILED(Ready_Layer_FireAvatar(TEXT("Layer_FireAvatar"))))
		return E_FAIL;

}

void CLevel_FireAvatar::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_FireAvatar::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	SetWindowText(g_hWnd, TEXT("튜토리얼 레벨입니다."));

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	if (m_isBattle) {

		wsprintf(HitMsg, TEXT("HITS"));
		if (FAILED(pGameInstance->Render_Fonts(TEXT("Font_Javan40"), HitMsg, _float2(1787, 217/*g_iWinCX / 2 + 700, g_iWinCY / 2 - 200*/), XMVectorSet(0.9f, 1.f, 0.7f, 1.f))))
			return E_FAIL;

		wsprintf(DamageMsg, TEXT("DAMAGES"));
		if (FAILED(pGameInstance->Render_Fonts(TEXT("Font_Javan40"), DamageMsg, _float2(1747, 267/*g_iWinCX / 2 + 650, g_iWinCY / 2 - 150*/), XMVectorSet(0.9f, 1.f, 0.7f, 1.f))))
			return E_FAIL;

		wsprintf(ComboHit, TEXT("%d"), combohitNum);
		if (FAILED(pGameInstance->Render_Fonts(TEXT("Font_Javan50"), ComboHit, _float2(1680, 150), XMVectorSet(0.9f, 1.f, 0.7f, 1.f))))
			return E_FAIL;


		wsprintf(DamageHit, TEXT("%d"), damageNum);
		if (FAILED(pGameInstance->Render_Fonts(TEXT("Font_Javan50"), DamageHit, _float2(1680, 210), XMVectorSet(0.9f, 1.f, 0.7f, 1.f))))
			return E_FAIL;

	}

	return S_OK;
}

HRESULT CLevel_FireAvatar::Ready_Layer_FireAvatar(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (nullptr == pGameInstance->Add_GameObjectToLayer(LEVEL_LORD_BALSEPH, pLayerTag, TEXT("Prototype_GameObject_FireAvatar")))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_FireAvatar::Ready_Map(const char * pModelFilePath, const char * pModelFileName, _vector vCenterPos)
{
	return S_OK;
}

CLevel_FireAvatar * CLevel_FireAvatar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_FireAvatar*	pInstance = new CLevel_FireAvatar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Tutorial"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_FireAvatar::Free()
{
	__super::Free();

	Safe_Release(m_pBattle_Manager);
}