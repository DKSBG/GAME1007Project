#pragma once
#include "gameObject.h"

class CollideInfo
{
public:
	CollideInfo();
	GameObject* pGameObject;
	Vector2 detectRange;
};