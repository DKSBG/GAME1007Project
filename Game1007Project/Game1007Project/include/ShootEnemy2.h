#pragma once
#include "reactableItem.h"
#include "gun.h"

class ShootEnemy2 : public Ship
{
public:
	void Update();
	void Init();
	void Attack();
	void Move();
private:
	Gun* m_pGun;
};
