#pragma once
#include "gameObject.h"
#include <vector>

class PlayerUI : public GOComponent 
{
public:
	void Init();
	void SetUIPlayTimes(int times);
	void UIBossHPEnable(bool enable);
	void SetBossHP(float rate);
	void UIProgressEnable(bool enable);
	void SetProgressPosition(float rate);
private:
	void InitUIPlayerTimes();
	void InitUIBossHP();
	void InitPlayerProgress();
	GameObject* m_pPlayerTimesArea;
	GameObject* m_pBossHP;
	GameObject* m_pPlayerShipIcon;
	std::vector<GameObject*> m_pPlayerTimeIcons;
};