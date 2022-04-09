#pragma once
#include "gameObject.h"


class Explode : public GOComponent 
{
public:
	void Update();
private:
	long m_explodeTimer = 500;
};