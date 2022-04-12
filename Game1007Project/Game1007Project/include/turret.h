#pragma once
#include "reactableItem.h"
#include "gun.h"

class Turret : public Ship
{
public:
	void Update();
	void Init();
	void Attack();
private:
	Gun* m_pGun;
};
