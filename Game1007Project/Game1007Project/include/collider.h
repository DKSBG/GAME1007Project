#pragma once
#include "gameObject.h"
#include "collideInfo.h"
#include "colliderManager.h"

//enum ColliderType {Ally, Enemy, ThirdPart, Other};

class Collider : GOComponent
{
public:
	//ColliderType type = ColliderType::Other;
	CollideInfo* colliderInfo;
	void Init();
};
