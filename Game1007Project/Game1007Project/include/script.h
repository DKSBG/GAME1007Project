#pragma once
#include"gameObject.h"

class ExampleShipScript : GOComponent
{
public:
	void Draw();
	void Update();
};

class ExampleProjectileScript : GOComponent
{
public:
	void Draw();
	void Update();
	void SetFlyVector(Vector2 vector);
private:
	Vector2 m_flyVector;
};
