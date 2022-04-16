#pragma once
#include "gameObject.h"

class CollideInfo
{
public:
	bool enable = true;
	CollideInfo();
	GameObject* pGameObject;
	Vector2 detectRange;
};