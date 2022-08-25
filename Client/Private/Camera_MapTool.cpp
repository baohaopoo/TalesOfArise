#include "stdafx.h"
#include "..\Public\Camera_MapTool.h"
#include "GameInstance.h"

CCamera_MapTool::CCamera_MapTool(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CCamera(pDeviceOut, pDeviceContextOut)
{
}

CCamera_MapTool::CCamera_MapTool(const CCamera_MapTool & rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_MapTool::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_MapTool::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (nullptr != pArg)
	{
		memcpy(&m_CameraDesc, pArg, sizeof(CAMERADESC));

		m_CurEye = m_CameraDesc.vEye;
		m_CurAt = m_CameraDesc.vAt;
	}

	return S_OK;
}

void CCamera_MapTool::Tick(_double TimeDelta)
{
	// Eye At���� �����Ѵ�.
	Cal_CurEyeAt();

	// �Ÿ� �� �����ϱ�
	Cal_Distance();

	// ���� �����ϱ�
	Cal_Degree();


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	if (pGameInstance->Key_Pressing(DIK_LSHIFT)) {

		if (pGameInstance->Get_DIKeyState(DIK_W) & 0x8000)
		{
			m_pTransformCom->Go_Straight(TimeDelta);
		}
		if (GetKeyState('S') & 0x8000)
		{
			m_pTransformCom->Go_BackWard(TimeDelta);
		}
		if (GetKeyState('A') & 0x8000)
		{
			m_pTransformCom->Go_Left(TimeDelta);
		}
		if (GetKeyState('D') & 0x8000)
		{
			m_pTransformCom->Go_Right(TimeDelta);
		}

		_long		MouseMove;

		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
		{
			m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta * MouseMove * 0.003f);
		}

		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), TimeDelta * MouseMove* 0.003f);
		}
	}
	else {
		// Ű ó��
		Press_Key(TimeDelta);
	}

	__super::Tick(TimeDelta);

	RELEASE_INSTANCE(CGameInstance);
}

void CCamera_MapTool::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CCamera_MapTool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CCamera_MapTool::Adjust_Angle(_float fDegree)
{
	// ī�޶��� Angle ���� �����ϰ�, �ش� ������ ī�޶��� at ���� �����Ѵ�.
	int iAngle = (int)fDegree;
	m_fDegreeUD = (_float)iAngle;

	// �ٲ� �������� ����Ͽ� ī�޶��� at���� �����Ѵ�.

	// �������� m_fDistance��ŭ ������ ��ġ�� �ִ� ���� �����.
	Cal_Distance();
	_float3 vPos = _float3(0.f, 0.f, m_fDistance);




	// �ش� ���� x������ m_fDegreeUD��ŭ ������.
	_float4x4 matfloat4x4;
	_matrix mat = XMMatrixIdentity();
	XMStoreFloat4x4(&matfloat4x4, mat);
	memcpy(matfloat4x4.m[3], &vPos, sizeof(_float3));

	mat = XMLoadFloat4x4(&matfloat4x4);
	mat = mat * XMMatrixRotationX(XMConvertToRadians(m_fDegreeUD));
	XMStoreFloat4x4(&matfloat4x4, mat);
	memcpy(&vPos, matfloat4x4.m[3], sizeof(_float3));




	// �ش� ���� y������ m_fDegreeLR��ŭ ������.
	mat = XMMatrixIdentity();
	XMStoreFloat4x4(&matfloat4x4, mat);
	memcpy(matfloat4x4.m[3], &vPos, sizeof(_float3));

	mat = XMLoadFloat4x4(&matfloat4x4);
	mat = mat * XMMatrixRotationY(XMConvertToRadians(m_fDegreeLR));
	XMStoreFloat4x4(&matfloat4x4, mat);
	memcpy(&vPos, matfloat4x4.m[3], sizeof(_float3));




	// ī�޶��� eye���� �����´�.	
	_vector vEye = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	// ī�޶��� at���� ���Ѵ�.
	_vector vAt = vEye + XMLoadFloat3(&vPos);

	// ī�޶��� ��ġ�� �ٽ� �����Ѵ�.
	SetPos(vEye, vAt, XMVectorSet(0.f, 1.f, 0.f, 1.f));
}

void CCamera_MapTool::Rotation(_float fDegree)
{
	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), XMConvertToRadians(fDegree));
	m_fDegreeLR = fDegree;
}

void CCamera_MapTool::Cal_CurEyeAt(void)
{
	XMStoreFloat3(&m_CurEye, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	_vector vLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	XMStoreFloat3(&m_CurAt, XMVector3Normalize(vLook) + XMLoadFloat3(&m_CurEye));
}

void CCamera_MapTool::Cal_Distance(void)
{
	_vector vEye = XMLoadFloat3(&m_CurEye);
	_vector vAt = XMLoadFloat3(&m_CurAt);

	m_fDistance = XMVectorGetX(XMVector3Length(vAt - vEye));
}

void CCamera_MapTool::Cal_Degree(void)
{
	// look ���� ���͸� ���Ѵ�.
	_vector vLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);

	// �ش� ������ y���� 0���� �ϸ� xz������ ���� ���Ͱ� ���´�.
	_vector vLook_xz = XMVectorSetY(vLook, 0.f);

	// �� ���⺤���� ���̰��� ���Ѵ�.
	_vector vDot = XMVector3Dot(vLook, vLook_xz);
	_vector fRadin = XMVectorACos(vDot / (XMVector3Length(vLook) * XMVector3Length(vLook_xz)));
	_float fDegree = XMConvertToDegrees(XMVectorGetX(fRadin));

	// ��������� ���� �����Ѵ�
	// ���� eye�� y������ at�� y���� �� ũ�ٸ� ������ ���Ѵ�.
	if (m_CurEye.y < m_CurAt.y)
		m_fDegreeUD *= -1.f;

	m_fDegreeUD = fDegree;
}

void CCamera_MapTool::SetPos(_fvector vEye, _fvector vAt, _fvector vUpAxis)
{
	_vector		vLook = vAt - vEye;
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

	_vector		vRight = XMVector3Cross(vUpAxis, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));

	_vector		vUp = XMVector3Cross(vLook, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));

	_vector		vPosition = XMVectorSetW(vEye, 1.f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);

	XMStoreFloat3(&m_CurEye, vEye);
	XMStoreFloat3(&m_CurAt, vAt);
}

void CCamera_MapTool::Press_Key(_double TimeDelta)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);

	if (pGameInstance->Key_Pressing(DIK_W))
	{
		m_pTransformCom->Go_Straight_PlaneXZ(TimeDelta);
	}
	if (pGameInstance->Key_Pressing(DIK_S))
	{
		m_pTransformCom->Go_BackWard_PlaneXZ(TimeDelta);
	}
	if (pGameInstance->Key_Pressing(DIK_A))
	{
		m_pTransformCom->Go_Left(TimeDelta);
	}
	if (pGameInstance->Key_Pressing(DIK_D))
	{
		m_pTransformCom->Go_Right(TimeDelta);
	}

	if (!pGameInstance->Key_Pressing(DIK_R)) {
		if (pGameInstance->Key_Pressing(DIK_NUMPADPLUS))
		{
			m_pTransformCom->Go_BackWard(TimeDelta);
		}
		if (pGameInstance->Key_Pressing(DIK_NUMPADMINUS))
		{
			m_pTransformCom->Go_Straight(TimeDelta);
		}
	}

	//// +,-Ű�� ������ ���
	//if (pGameInstance->Get_DIKeyState(DIK_NUMPADPLUS)) {
	//	if (!pGameInstance->Get_DIKeyPreState(DIK_NUMPADPLUS))
	//		Adjust_Angle(true);
	//}
	//if (pGameInstance->Get_DIKeyState(DIK_NUMPADMINUS)) {
	//	if (!pGameInstance->Get_DIKeyPreState(DIK_NUMPADMINUS))
	//		Adjust_Angle(false);
	//}

	Safe_Release(pGameInstance);
}

CCamera_MapTool * CCamera_MapTool::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCamera_MapTool*	pInstance = new CCamera_MapTool(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_MapTool"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_MapTool::Clone(void * pArg)
{
	CCamera_MapTool*	pInstance = new CCamera_MapTool(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_MapTool"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_MapTool::Free()
{
	__super::Free();

}
