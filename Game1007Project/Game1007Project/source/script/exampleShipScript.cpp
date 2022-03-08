#include"Script.h"

// Script component no need to draw.
void ExampleShipScript::Draw() {}

// This metherd is called by engine each frame.
void ExampleShipScript::Update()
{
	Vector2* pps = transform->position;
	pps->x += 1;
	transform->position = pps;
}
