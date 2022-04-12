#pragma once
#include "reactableItem.h"
#include "gun.h"

class BasicShootEnemy : public Ship
{
public:
	void Update();
	void Init();
	void Attack();
	void Move();
private:
	Gun* m_pGun;
};
