#include "collider.h"

void Collider::Init()
{
	colliderInfo = new CollideInfo();
	colliderInfo->pGameObject = this->gameObject;
	colliderInfo->detectRange = new Vector2(1, 1);
	CollideManager::GetInstanse()->AddCollider(colliderInfo);
}