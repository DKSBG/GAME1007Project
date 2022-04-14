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
};