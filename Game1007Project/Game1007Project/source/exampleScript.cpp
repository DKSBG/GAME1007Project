#include"Script.h"

// Script component no need to draw.
void ExampleScript::Draw() {}

// This metherd is called by engine each frame.
void ExampleScript::Update()
{
	Vector2* pps = transform->position;
	pps->x += 1;
	transform->position = pps;
}
