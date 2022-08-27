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

// ĳ���Ͱ� ��������Ʈ �̿��, �ش� ��ü�� ���� ��ġ�� �̵��ϰ�, ĳ������ ī�޶�� m_vCameraLook������ �ٶ󺸰� �Ѵ�.

class CWayPoint_Pos final : public CGameObject
{
public:
	typedef struct _tagWayPoint_DESC {
		_float3		fPos;			// ���� ����Ʈ�� ��ġ
		_float3		fMovePos;		// ���� ����Ʈ�� �Ű��� ��ġ
		CPlayer* pTargetPlayer = nullptr;	// �浹 ó���� �� �÷��̾� ������Ʈ ����
	} WayPoint_DESC;

private:
	CWayPoint_Pos(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CWayPoint_Pos(const CWayPoint_Pos& rhs);
	virtual ~CWayPoint_Pos() = default;

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
	_float3		m_fMovePos;

public:
	static CWayPoint_Pos* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END