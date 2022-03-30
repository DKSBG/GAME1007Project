#include "reactableItem.h"
#include "tools.h"

void Ship::OnDie()
{
	Image* pImg;
	GameObject* pGoExplosion = new GameObject();
	pImg = new Image("Explosion1.png", 4);
	pGoExplosion->AddComponent<Image>(pImg);
	pGoExplosion->GetComponent<Image>()->SetNativeSize();

	Transform* explosionTrs = &pGoExplosion->transform;
	explosionTrs->scale.Set(2, 2);

	explosionTrs->position.x = this->transform->position.x;
	explosionTrs->position.y = this->transform->position.y;
	explosionTrs->position.x += this->transform->size.x * this->transform->scale.x / 2;
	explosionTrs->position.x -= explosionTrs->size.x * explosionTrs->scale.x / 2;
	explosionTrs->position.y += this->transform->size.y * this->transform->scale.y / 2;
	explosionTrs->position.y -= explosionTrs->size.y * explosionTrs->scale.y / 2;

	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}