#include "playerUI.h"
#include "dataParser.h"

PlayerInfo g_playerInfo{ 3 };

void PlayerUI::InitUIPlayerTimes()
{
	m_pPlayerTimesArea = PrefabParser::GetInstance()->Parser("playTimesArea.xml");
	m_pPlayerTimesArea->transform.localPosition.Set(10, 10);
	std::vector<GameObject*> pChildren = m_pPlayerTimesArea->GetChildren();
	for (int index = 0; index < pChildren.size(); index++)
	{
		m_pPlayerTimeIcons.push_back(pChildren[index]);
	}
}


void PlayerUI::SetUIPlayTimes(int times) 
{
	for (int index = 0; index < m_pPlayerTimeIcons.size(); index++) 
	{
		m_pPlayerTimeIcons[index]->isActive = (index <= times - 1);
	}
}

void PlayerUI::UIBossHPEnable(bool enable)
{
	m_pBossHP->GetParent()->isActive = enable;
}


void PlayerUI::SetBossHP(float rate)
{
	m_pBossHP->transform.scale.Set(rate, 1);
}

void PlayerUI::InitUIBossHP()
{
	m_pBossHP = PrefabParser::GetInstance()->Parser("bossHPArea.xml")->GetChildren()[0];
	m_pBossHP->GetParent()->transform.localPosition.Set(400, 10);
	m_pBossHP->GetParent()->isActive = false;
}

void PlayerUI::InitPlayerProgress()
{
	GameObject* go = PrefabParser::GetInstance()->Parser("progressArea.xml");
	go->transform.localPosition.Set(480, 13);
	m_pPlayerShipIcon = go->GetChildren()[0];
}

void PlayerUI::UIProgressEnable(bool enable) 
{
	m_pPlayerShipIcon->GetParent()->isActive = enable;
}

void PlayerUI::SetProgressPosition(float rate) 
{
	m_pPlayerShipIcon->transform.localPosition.x = (float)m_pPlayerShipIcon->GetParent()->transform.GetWidth() * rate;
}

void PlayerUI::Init() 
{
	InitUIPlayerTimes();
	InitUIBossHP();
	InitPlayerProgress();
}


