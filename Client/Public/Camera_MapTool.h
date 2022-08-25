#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Engine)

class CTransform;

END


BEGIN(Client)

class CCamera_MapTool final : public CCamera
{
private:
	explicit CCamera_MapTool(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCamera_MapTool(const CCamera_MapTool& rhs);
	virtual ~CCamera_MapTool() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();


public:
	void Adjust_Angle(_float fDegree);
	void Rotation(_float fDegree);
	void Cal_CurEyeAt(void);
	void Cal_Distance(void);
	void Cal_Degree(void);
	void SetPos(_fvector _Eye, _fvector _At, _fvector _Up);
	void Press_Key(_double TimeDelta);

public:
	_float Get_DegreeUD(void) { return m_fDegreeUD; }
	void Set_DegreeUD(_float fDegree) { m_fDegreeUD = fDegree; }

	_float Get_DegreeLR(void) { return m_fDegreeLR; }
	void Set_DegreeLR(_float fDegree) { m_fDegreeLR = fDegree; }

private:
	_float3		m_CurEye;		// ī�޶��� ���� Eye
	_float3		m_CurAt;		// ī�޶��� ���� At

	_float		m_fDegreeUD = 0.f;		// ī�޶��� ����(����)
	_float		m_fDegreeLR = 0.f;		// ī�޶��� ����(�¿�)
	_float		m_fDistance = 1.f;		// ī�޶��� eye�� at ������ �Ÿ�

	_bool		m_bChangeMove = false;	// ī�޶��� �������� tool�� �����ϴ��� ���ϴ����� ���� ����, true�� ���콺�� �����̰�, false�� ���� �����δ�.

public:
	static CCamera_MapTool* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END