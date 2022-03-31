#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void Obstacle::Init() 
{
	attribute.vector = new Vector2(0, 0);
	attribute.hp = 20000;
	attribute.speed = 0;
	attribute.atk = 1000;

	reactAttrbute.camp = Fiction::ThridPart;
	reactAttrbute.reactValue = -attribute.atk;
	reactAttrbute.target = ReactTarget::Both;
	reactAttrbute.type = ReactType::HP;
}

void Obstacle::OnDie()
{
	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}

void Obstacle::SpecificReact(ReactAttribute giverAttr) {}