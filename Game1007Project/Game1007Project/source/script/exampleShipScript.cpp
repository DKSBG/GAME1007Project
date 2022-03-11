#include"Script.h"

// This metherd is called by engine each frame.
void ExampleShipScript::Update()
{
	Vector2* pps = transform->position;
	pps->x += 1;
	transform->position = pps;
}
