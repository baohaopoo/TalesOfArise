#include "stdafx.h"
#include "..\Public\Level_FireAvatar.h"
#include "GameInstance.h"

#include "MapObject.h"
#include "WayPoint.h"
#include "WayPoint_Pos.h"
#include "Player.h"
#include "Navigation.h"
#include "Level_Loading.h"
#include "Owl.h"
#include "UI_Owl.h"
#include "Balseph_Stair.h"
#include "Lord_Balseph.h"
#include "Fire_Avatar.h"

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

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_FireAvatar(TEXT("Layer_FireAvatar"))))
		return E_FAIL;

	if (FAILED(Ready_Map("../Bin/Resources/Dat/Stage04/", "MeshList.dat", XMVectorSet(0.f, 0.f, 0.f, 1.f))))
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

	SetWindowText(g_hWnd, TEXT("Ʃ�丮�� �����Դϴ�."));

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

	CFire_Avatar* pFireAvatar = dynamic_cast<CFire_Avatar*>(pGameInstance->Add_GameObjectToLayer(LEVEL_FIRE_AVATAR, pLayerTag, TEXT("Prototype_GameObject_FireAvatar")));
	if (nullptr == pFireAvatar)
		return E_FAIL;

	CNavigation* pNavigation = nullptr;
	CTransform* pFireAvatar_Transform = dynamic_cast<CTransform*>(pFireAvatar->Get_Component(TEXT("Com_Transform")));
	pNavigation = pFireAvatar->SetUp_Navigation(TEXT("Prototype_Component_Navigation_Map_FireAvatar"));
	pFireAvatar_Transform = dynamic_cast<CTransform*>(pFireAvatar->Get_Component(TEXT("Com_Transform")));

	_float3 fPos = _float3(23.28f, -10.f, -0.13f);
	pFireAvatar_Transform->Move(fPos);
	pNavigation->Find_My_Cell(XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f));
	pFireAvatar_Transform->Move(fPos.x, pFireAvatar_Transform->Get_Height(pNavigation), fPos.z);



	_vector vPlayerPos = dynamic_cast<CTransform*>(m_pPlayerAlphen->Get_Component(TEXT("Com_Transform")))->Get_State(CTransform::STATE_POSITION);
	_vector vFireAvatarPos = dynamic_cast<CTransform*>(pFireAvatar->Get_Component(TEXT("Com_Transform")))->Get_State(CTransform::STATE_POSITION);

	_vector vLook = vPlayerPos - vFireAvatarPos;
	dynamic_cast<CTransform*>(pFireAvatar->Get_Component(TEXT("Com_Transform")))->Look(vLook);

	
	CLord_Balseph* pLord_Balseph = CBattle_Manager::GetInstance()->Get_Lord_Balseph();

	if (nullptr != pLord_Balseph) {
		pNavigation = nullptr;
		CTransform* pBalseph_TransformCom = nullptr;

		pNavigation = pLord_Balseph->SetUp_Navigation(TEXT("Prototype_Component_Navigation_Map_FireAvatar"));
		pBalseph_TransformCom = dynamic_cast<CTransform*>(pLord_Balseph->Get_Component(TEXT("Com_Transform")));
		pBalseph_TransformCom->Move(0.f, 0.f, 0.f);
		pNavigation->Find_My_Cell(XMVectorSet(0.f, 0.f, 0.f, 1.f));
		pBalseph_TransformCom->Move(0, pBalseph_TransformCom->Get_Height(pNavigation), 0);
	}

	


	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_FireAvatar::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	// Skybox ����
	if (nullptr == pGameInstance->Add_GameObjectToLayer(LEVEL_FIRE_AVATAR, LAYER_MAPTOOL_Skybox, TEXT("Prototype_GameObject_Sky")))
		return E_FAIL;

	// Alphen ����
	CLayer* pLayerPlayer = pGameInstance->Find_Layer(LEVEL_STATIC, pLayerTag);

	if (nullptr == pLayerPlayer) {
		MSG_BOX(TEXT("CLevel_Balseph : No Player Detected"));
		return E_FAIL;
	}

	m_pPlayerAlphen = dynamic_cast<CPlayer*>(*pLayerPlayer->Get_ObjectList().begin());

	if (nullptr == m_pPlayerAlphen)
		return E_FAIL;

	CNavigation* pNavigation = nullptr;
	CTransform* pAlphen_TransformCom = nullptr;

	// ���� Navigation Mesh�� Alphen�� Ÿ�� ��.
	pNavigation = m_pPlayerAlphen->SetUp_Navigation(TEXT("Prototype_Component_Navigation_Map_FireAvatar"));

	pAlphen_TransformCom = dynamic_cast<CTransform*>(m_pPlayerAlphen->Get_Component(TEXT("Com_Transform")));
	pAlphen_TransformCom->Move(-95.22, -3.95, -0.11);
	pNavigation->Find_My_Cell(XMVectorSet(-95.22, -3.95, -0.11, 1.f));
	pAlphen_TransformCom->Move(-95.22, pAlphen_TransformCom->Get_Height(pNavigation), -0.11);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_FireAvatar::Ready_Map(const char * pModelFilePath, const char * pModelFileName, _vector vCenterPos)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	char szFullPath[MAX_PATH] = "";

	strcpy_s(szFullPath, pModelFilePath);
	strcat_s(szFullPath, pModelFileName);

	TCHAR szCurPath[MAX_PATH] = TEXT("");
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szFullPath, (int)strlen(szFullPath), szCurPath, MAX_PATH);

	// ������ ����.
	HANDLE		hFile = CreateFile(szCurPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD		dwByte = 0;
	DWORD		dwStrByte = 0;

	CMapObject::MAPOBJDesc Desc;

	while (true)
	{
		// ���ڿ� �޸��� ũ�⸦ ����
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

		// �о�� �޸��� ũ�⸸ŭ ���ڿ��� �Ҵ��ϰ�, �ش� ���ڿ��� �о��
		TCHAR*	pName = new TCHAR[dwStrByte];
		ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

		// �߸����� ��� �ش� �޸� ���� �� ���߱�
		if (0 == dwByte)
		{
			delete[]pName;
			break;
		}

		// Desc�� ���� �ֱ�
		Desc.pPrototype_ObjectName = pName;

		// Collider ���� ����
		Desc.fColliderSize = _float3(10.f, 10.f, 10.f);

		// ��� ������ ����
		ReadFile(hFile, &Desc.TransformMatrix, sizeof(_float4x4), &dwByte, nullptr);

		_float4x4 matWorld4x4;
		XMStoreFloat4x4(&matWorld4x4, XMMatrixIdentity());

		_float3 fPos;
		XMStoreFloat3(&fPos, vCenterPos);
		memcpy(&matWorld4x4.m[CTransform::STATE_POSITION], &fPos, sizeof(_float3));

		// ���Ͽ��� ���� ���� ���ڷ� ���� ���� ��ġ�� ���Ͽ� ������Ʈ���� �ش� ��ġ�� �̵���Ų��.
		XMStoreFloat4x4(&Desc.TransformMatrix, XMMatrixMultiply(XMLoadFloat4x4(&Desc.TransformMatrix), XMLoadFloat4x4(&matWorld4x4)));



		// �� ���� Ȯ��
		ReadFile(hFile, &Desc.m_bMap, sizeof(_bool), &dwByte, nullptr);

		Desc.eLevel = LEVEL_STATIC;

		if (!_tcscmp(Desc.pPrototype_ObjectName, TEXT("Prototype_Component_Model_Map_GrandYork_Battle_02")) ||
			!_tcscmp(Desc.pPrototype_ObjectName, TEXT("Prototype_Component_Model_Map_GrandYork_Battle_02_NaviMap")) ||
			!_tcscmp(Desc.pPrototype_ObjectName, TEXT("Prototype_Component_Model_Map_GrandYork_Battle_04")) ||
			!_tcscmp(Desc.pPrototype_ObjectName, TEXT("Prototype_Component_Model_Map_GrandYork_Battle_04_NaviMap"))
			) {
			Desc.eLevel = LEVEL_STATIC;
		}

		// �ش� ������Ʈ�� �̸��� Owl�� ���
		if (!_tcscmp(Desc.pPrototype_ObjectName, TEXT("Prototype_Component_Model_Owl_001"))) {
			// �� ������Ʈ ����
			COwl::OwlDesc OwlDesc;
			OwlDesc.TransformMatrix = Desc.TransformMatrix;
			OwlDesc.fDistance = 5.f;
			OwlDesc.pModelTag = Desc.pPrototype_ObjectName;
			OwlDesc.pTargetPlayer = m_pPlayerAlphen;

			COwl* pOwl = dynamic_cast<COwl*>(pGameInstance->Add_GameObjectToLayer(LEVEL_FIRE_AVATAR, LAYER_MAPTOOL_Owls, TEXT("Prototype_GameObject_Owl"), &OwlDesc));
			// ���⼭ UI �Ŵ����� Owl�� ������ UI�� �����Ͽ� �־��ش�.
			// ~~
		}
		else {
			// �� ������Ʈ ����
			CMapObject* pMapObject = dynamic_cast<CMapObject*>(pGameInstance->Add_GameObjectToLayer(LEVEL_FIRE_AVATAR, LAYER_MAPTOOL_PlacedObjects, TEXT("Prototype_GameObject_MapObject"), &Desc));
			m_vMapObject.push_back(pMapObject);
		}
	}

	// ������ �ݴ´�.
	CloseHandle(hFile);

	RELEASE_INSTANCE(CGameInstance);

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