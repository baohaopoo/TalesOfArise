#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)

class CShader;
class CCollider;
class CRenderer;
class CModel;
class CNavigation;

END

BEGIN(Client)

class CPlayer;
class CUI_Owl;

class COwl final : public CGameObject {
public:
	enum OWL_ANIM_STATE {
		OWL_IN_POSITION_IDLE,						// 0000 ���ڸ� - IDLE
		OWL_IN_POSITION_IDLE_LONG,					// 0001 ���ڸ� - IDLE ���

		OWL_IN_POSITION_OPEN_WING,					// 0031 ���ڸ� - ���� ��ģ���� ����

		OWL_IN_POSITION_TILT_HEAD,					// 0060 ���ڸ� - �� ����װŸ���

		OWL_IN_POSITION_WINGING_FAST,				// 0070 ���ڸ� - ������ ������

		OWL_IN_POSITION_WINGING_SLOW,				// 0080 ���ڸ� - õõ�� ������

		OWL_IN_POSITION_LOOK_AROUND,				// 0090 ���ڸ� - �������� �ѷ�����

		OWL_IN_POSITION_FLAP_WINGS,					// 0100 ���ڸ� - ���� �θ��� ����

		OWL_IN_POSITION_BREATH_DEEP,				// 0120 ���ڸ� - �� ũ�Խ����� �����

		OWL_IN_POSITION_LOSE_HEART,					// 0130 ���ڸ� - �����ϱ�
		OWL_IN_POSITION_LOSE_HEART_KEEP,			// 0131 ���ڸ� - ������ ���¿��� �� ��� ���̰� �ֱ�
		OWL_IN_POSITION_LOSE_HEART_RETURN,			// 0132 ���ڸ� - �� ���� ���¿��� �����·� ����

		OWL_IN_POSITION_GLARE,						// 0160 ���ڸ� - ���� �������
		OWL_IN_POSITION_GLARE_KEEP,					// 0161 ���ڸ� - ����� ���� ����
		OWL_IN_POSITION_GLARE_RETURN,				// 0162 ���ڸ� - �������� �����·� ����

		OWL_IN_POSITION_TILT_BACK,					// 0170 ���ڸ� - �� �ڷ� ������ ���� ��ġ��
		OWL_IN_POSITION_TILT_BACK_KEEP,				// 0171 ���ڸ� - �� �ڷ� ���� ���� ����
		OWL_IN_POSITION_TILT_BACK_RETURN,			// 0172 ���ڸ� - �� �ڷ� ���� ���¿��� �����·� ����

		OWL_IN_POSITION_DOZE,						// 0180 ���ڸ� - �ٹ��ٹ� ����
		OWL_IN_POSITION_DOZE_KEEP,					// 0181 ���ڸ� - ���� ���� ����
		OWL_IN_POSITION_DOZE_RETURN,				// 0182 ���ڸ� - ���� �����·� ����

		OWL_IN_POSITION_TO_FLYING,					// 0200 ������ - ���ڸ����� �������ؼ� ���ֱ�
		OWL_IN_FLYING_KEEP,							// 0201 ������ - �������ؼ� ���ִ� ���� ����
		OWL_IN_FLYING_TO_POSITION,					// 0202 ������ - ���ִٰ� �ٽ� �����·� ����

		OWL_IN_FLYING_TRUN_BACKWARD,				// 0210 ������ - ���ִ� ���¿��� �ڷ� �ѹ��� ����

		OWL_IN_FLYING_TRUN_SIDE_TO_SIDE,			// 0230 ������ - ���ִ� ���¿��� �¿�� �ѹ��� ����

		OWL_IN_POSITION_TO_AWAY_DIAGONALLY,			// 0240 ������ - ���ڸ����� �밢������ ���ư���

		OWL_IN_POSITION_TO_AWAY_DIAGONALLY_UP,		// 0250 ������ - ���ڸ����� �밢������ ���ư��� ���� ����

		OWL_IN_POSITION_TO_AWAY_UP,					// 0260 ������ - ���ڸ����� ���� ���ư���
		OWL_END
	};

	/*
		�⺻ : ���ڸ� - IDLE
		����� : ���ڸ� - IDLE ���

		
		��ȣ�ۿ��ϱ� ������, ��ȣ�ۿ��� ������ ������ �� 2������ 


		01 : ���ڸ� - ���� ��ģ���� ����
		02 : 
	
	
	
	*/



public:
	typedef struct _tagOwlDesc {
		_float4x4	TransformMatrix;	// �̵� ���
		_float fDistance;	// �÷��̾���� �Ÿ�
		const TCHAR* pTagItemName = nullptr;	// ������ �̸�
		const TCHAR* pModelTag = nullptr;	// �� �̸�
		CPlayer* pTargetPlayer = nullptr;	// Ÿ���� �Ǵ� �÷��̾� ����
	}OwlDesc;

private:
	COwl(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	COwl(const COwl& rhs);
	virtual ~COwl() = default;

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
	CCollider*			m_pSphereCom = nullptr;

private:
	HRESULT SetUp_Components(void* pArg);
	HRESULT SetUp_ConstantTable();

public:
	static COwl* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

private:
	void Check_Collision(void);
	_bool m_bEncounter = false;

public:
	void Set_InRange(_bool bInRange) { m_bInRange = bInRange; }			// ���� ���� �÷��̾ �ִ��� Ȯ���Ͽ� 
	void Set_TargetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }	// Ÿ���� �Ǵ� �÷��̾� ����


	void Check_InRange(void);

private:
	_uint m_iCurrentAnimationIndex = 0;
	_uint m_iNextAnimationIndex = 0;

	CPlayer* m_pPlayer = nullptr;		// Ÿ���� �Ǵ� �÷��̾� ����
	_float m_fDistance;		// Ÿ�ٰ��� �Ÿ� ����, Ÿ�ٰ� �Ÿ��� �ش� ������ �������, �������� �����Ѵ�.
	
	_bool m_bInRange = false;			// Ÿ�� �÷��̾ ���� ���� ���� ������ true, Ư�� �ִϸ��̼��� �۵��Ѵ�.

	_bool m_bInRoop = true;				// �÷��̾ xŰ�� ������ ������ ���� �ִϸ��̼��� �ݺ��Ѵ�. ������ ���� false�� �ǰ�, �ξ��̰� ���ư���.

	_bool m_bDone = false;				// ��� ��ȣ�ۿ��� ���� ���¶�� true, �ƴ϶�� false, �ش� ������ true�̸� �� �̻� ������Ʈ�� �۵����� �ʴ´�.

	// �ξ��̴� �÷��̾ �������� ���� ������ �ϴ� �ִϸ��̼ǰ� ��ȣ�ۿ�� �ִϸ��̼��� �ִ�.

	// OWL_IN_POSITION_IDLE | OWL_IN_POSITION_IDLE_ACTIVE ���·� ������ �ִٰ�, �÷��̾ ���� ���� ���� ������ 
	
	// OWL_IN_POSITION_TO_FLY -> OWL_IN_FLY_SPIN_AROUND -> OWL_IN_FLY_IDLE(IDLE ����)
	// OWL_IN_POSITION_TILT_HEAD
	// OWL_IN_POSITION_FLAPPING
	
	// �� 3���� �ϳ��� �ൿ�� �� ��

	// OWL_IN_FLYAWAY_FORWARD_UPDOWN | OWL_IN_FLYAWAY_FORWARD_UPSTRAIGHT | OWL_IN_FLYAWAY_MOVEUP �� �ϳ��� �ִϸ��̼��� ����Ѵ�.
	// ����, ������Ʈ�� �����ϰų� ������� �ʴ´�.

	// 

private:
	const TCHAR* m_TagItemp = nullptr;		// ������ ����, ���߿� ������ class�� �����, ���⿡ ������ ������ �־��ش�. �켱 �̸��� �༭ UI ��ȣ�ۿ뿡 ���.



private:
	_uint m_iOwlNumber = 14;

	CUI_Owl* m_pInteractionUI = nullptr;

};

END