#pragma once
#include"gameObject.h"

class ExampleShipScript : GOComponent
{
public:
	void Update();
};

class ExampleProjectileScript : GOComponent
{
public:
	void Update();
	void SetFlyVector(Vector2 vector);
private:
	Vector2 m_flyVector;
};
