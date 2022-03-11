#include"Script.h"

// This metherd is called by engine each frame.
void ExampleProjectileScript::Update()
{
	Vector2* pPosition = transform->position;
	pPosition->x += m_flyVector.x;
	pPosition->y += m_flyVector.y;
	transform->position = pPosition;
}

void ExampleProjectileScript::SetFlyVector(Vector2 vector) 
{
	m_flyVector.x = vector.x;
	m_flyVector.y = vector.y;
}
