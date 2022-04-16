#pragma once
#include "reactableItem.h"
#include "camera.h"
#include "gun.h"

class BossShip : public Ship
{
public:
	void Update();
	void Init();
	void OnExplode();
	void SpecificReact(ReactableItem* giver);
private:
	void Idle();
	void Fire();
	void CallShip();
	void MMove();
	Camera* m_pCam;
	Image* m_pImg;
	float m_lastCamPosX;
	Gun* m_basicGun;
	long m_cdTimer;
	long m_cdTime;
	long m_actionTimes;
	long m_actionCount;
	bool m_isActing;
	int m_currentIndex = 1;
	int m_maxHp;
	bool m_start;
};