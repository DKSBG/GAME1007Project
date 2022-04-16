#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void Projectile::Init() 
{
	m_pImg = gameObject->GetComponent<Image>();
}

void Projectile::Update() {}

void Projectile::OnDie()
{
	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}

void Projectile::SpecificReact(GameObject* go) {}