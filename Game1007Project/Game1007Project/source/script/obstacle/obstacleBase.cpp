#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void Obstacle::Init() 
{
	itemAttribute.vector.Set(0, 0);
	itemAttribute.hp = 20000;
	itemAttribute.speed = 0;
	itemAttribute.atk = 1000;

	reactAttrbute.fiction = Fiction::Enemy;
	reactAttrbute.reactValue = -itemAttribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;
}

void Obstacle::OnDie()
{
	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}