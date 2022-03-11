#pragma once
#include "gameObject.h"
#include "collideInfo.h"
#include "colliderManager.h"

class Collider : GOComponent
{
public:
	CollideInfo* colliderInfo;
	void Init();
};
