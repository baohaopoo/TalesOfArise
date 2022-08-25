#pragma once
#include "Client_Defines.h"
#include "Level.h"
#include "Battle_Manager.h"

BEGIN(Client)

class CMapObject;
class CWayPoint;
class CPlayer;

END

BEGIN(Client)

class CLevel_BossLevel1 final : public CLevel
{
private:
	explicit CLevel_BossLevel1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_BossLevel1() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Lights();
	HRESULT Ready_Layer_Balseph(const _tchar * pLayerTag);
	HRESULT Ready_Layer_FireAvatar(const _tchar * pLayerTag);
	HRESULT Ready_Layer_Fire_Deco(const _tchar * pLayerTag);

	
private:
	HRESULT Ready_Map(const char * pModelFilePath, const char * pModelFileName, _vector vCenterPos);
	HRESULT Ready_Map_Battle02(_vector vCenterPos);		// CenterPos�� �������� Battle02�� ������Ʈ���� ����
	HRESULT Ready_Map_Battle04(_vector vCenterPos);		// CenterPos�� �������� Battle04�� ������Ʈ���� ����

private:
	_float4x4  matBattle02World;		// Prototype_Component_Model_Map_GrandYork_Battle_02
	_float4x4  matBattle04World;		// Prototype_Component_Model_Map_GrandYork_Battle_04

private:
	vector<CMapObject*>	m_vMapObject;	// ��ġ�� �� ������Ʈ vector
	vector<CWayPoint*>	m_vWayPoints;	// ��ġ�� �� ������Ʈ vector

public:
	CBattle_Manager* m_pBattle_Manager = nullptr;
	typedef struct tagUIInfo {
		_float fX;
		_float fY;
		_float fCX;
		_float fCY;

	}UIINFO;

private:
	CPlayer* m_pPlayerAlphen = nullptr;

private:
	_tchar HitMsg[MAX_PATH] = TEXT("");
	_tchar DamageMsg[MAX_PATH] = TEXT("");
	_tchar StatusLine[MAX_PATH] = TEXT("");
	_tchar ComboHit[MAX_PATH] = TEXT("");
	_tchar DamageHit[MAX_PATH] = TEXT("");
	int combohitNum = 0;
	int damageNum = 0;
	bool m_isComboHit = false;
	bool m_isInvenOpen = false;
	bool m_isFirst = true;
	_float smashuiTime = 0;
	int next = 0;
	int LineMsgSprite = 1;
	bool m_isBattle = false;
	bool LineMsgCreate = false;
	bool m_isBattleOn = false;
	float fontpos = 0;
	bool m_isHit = false;
	float HitPos, DamagePos;
	bool m_bFirstBattleUI = false;
public:
	static CLevel_BossLevel1* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END