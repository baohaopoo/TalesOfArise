#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "VIBuffer_Rect.h"
#include "GameInstance.h"

BEGIN(Client)

class CPicking_Rect final : public CGameObject
{
public:
	typedef struct _tagPicking_RectDesc {
		_float3		vPos;			// �簢���� ����
		_float2		fSize;			// �簢���� ����/���� ����
	}Picking_RectDESC;

private:
	CPicking_Rect(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CPicking_Rect(const CPicking_Rect& rhs);
	virtual ~CPicking_Rect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
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
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

public:
	_float3*	Get_RectPos(void) { return m_RectPos; }
	void		Change_Height(_float fHeight);

private:
	_float3				m_RectPos[4];	// ��ŷ�� ���� �� 4���� ������ ��� �ִ� �迭, �� 0,1,2 / 0,2,3 �� ������ �ﰢ���� �����.
	_float3				m_vCenterPos;
	_uint				m_iSizeX;
	_uint				m_iSizeY;

public:
	static CPicking_Rect* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END