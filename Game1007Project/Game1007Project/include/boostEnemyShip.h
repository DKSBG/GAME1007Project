#pragma once
#include "reactableItem.h"

class BoostEnemyShip : public Ship
{
public:
	void Update();
	void Init();
	void Move();	
	float acceleration;
};