#include "collider.h"

void Collider::Init()
{
	colliderInfo.pGameObject = this->gameObject;
	CollideManager::GetInstanse()->AddCollider(&colliderInfo);
}