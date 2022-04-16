#pragma once
#include "gameObject.h"
#include "camera.h"
#include "enemyShip.h"

class GameController : public GOComponent
{
public:
	void Init();
	void Update();
private:
	Camera* m_pMainCam;
	Camera* m_pUICam;
	BossShip* m_boss = NULL;
	Ship* m_player = NULL;
	float m_bossMaxHp;
	float m_mapWeight = 5000;
	Image* m_resultPage;
	int m_resultDelay = 1500;
	bool m_isResult = false;
};