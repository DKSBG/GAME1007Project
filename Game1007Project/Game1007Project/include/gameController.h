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
	BossShip* m_boss = NULL;
	Ship* m_player = NULL;
	float m_bossMaxHp;
	float m_mapWeight = 100;
	//PlayerUI* ui = NULL;
};