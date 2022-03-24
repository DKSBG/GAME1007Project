#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void Projectile::Update() {}

void Projectile::OnDie()
{
	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}

void Projectile::SpecificReact(ReactAttribute giverAttr) {}