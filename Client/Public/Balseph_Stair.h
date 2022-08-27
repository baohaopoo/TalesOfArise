#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)

class CShader;
class CCollider;
class CRenderer;
class CModel;

END

BEGIN(Client)

class CPlayer;
class CLord_Balseph;

class CBalseph_Stair final : public CGameObject {
public:
	typedef struct _tagBalseph_StairDesc {
		_float4x4	TransformMatrix;	// �̵� ���
		const TCHAR* pModelTag = nullptr;		// �� �̸�
		CLord_Balseph* pTargetEnemy = nullptr;	// Ÿ���� �Ǵ� �� ������Ʈ ����(�ش� ���� ü���� �ִ� ü���� ���� ������, ����� �����´�.)
		CPlayer* pTargetPlayer = nullptr;		// Ÿ���� �Ǵ� �÷��̾� ������Ʈ ����(����� �������� ��, WayPoint�� �ش� �÷��̾��� ���ڸ� �޾� �ѱ��.)
	}Balseph_StairDesc;

private:
	CBalseph_Stair(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	CBalseph_Stair(const CBalseph_Stair& rhs);
	virtual ~CBalseph_Stair() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

private:
	HRESULT SetUp_Components(void* pArg);
	HRESULT SetUp_ConstantTable();

public:
	static CBalseph_Stair* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

public:
	void Activate_Stair(void) { m_bActivate = true; }
	void Set_EnemyTarget(CLord_Balseph* pTarget) { m_pTargetEnemy = pTarget; }

private:
	_bool m_bActivate = false;
	CLord_Balseph* m_pTargetEnemy = nullptr;
	CPlayer* m_pTargetPlayer = nullptr;
};

END