#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "GameInstance.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CPlayer;

// 캐릭터가 웨이포인트 이용시, 해당 객체의 월드 위치로 이동하고, 캐릭터의 카메라는 m_vCameraLook방향을 바라보게 한다.

class CWayPoint final : public CGameObject
{
public:
	typedef struct _tagWayPoint_DESC {
		_float3		fPos;			// 웨이 포인트의 위치
		LEVEL		eLevel;			// 상호작용시 바뀔 레벨의 정보, 해당 레벨로 이동한다.
		CPlayer* pTargetPlayer = nullptr;	// 충돌 처리를 할 플레이어 오브젝트 정보
	} WayPoint_DESC;

private:
	CWayPoint(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CWayPoint(const CWayPoint& rhs);
	virtual ~CWayPoint() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg, CTransform::TRANSFORMDESC* pTransformDesc = nullptr);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();

private:
	HRESULT SetUp_Components(void* pArg);
	HRESULT SetUp_ConstantTable();

private:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;

public:
	HRESULT Check_TargetPlayer_Collision(void);

public:
	void Set_TargetPlayer(CPlayer* pPlayer) { m_pTargetPlayer = pPlayer; }
	CPlayer* Get_TargetPlayer(void) { return m_pTargetPlayer; }

private:
	CPlayer*	m_pTargetPlayer = nullptr;
	LEVEL		m_eNextLevel = LEVEL_END;
	_bool		m_bMove = false;

public:
	static CWayPoint* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END