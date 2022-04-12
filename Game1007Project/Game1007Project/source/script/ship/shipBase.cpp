#include "reactableItem.h"
#include "tools.h"
#include "audioPlayer.h"
#include "explode.h"
#include "audioPlayer.h"

void Ship::OnDie()
{
	OnExplode();
}

void Ship::OnExplode()
{
	Image* pImg;
	GameObject* pGoExplosion = new GameObject();
	pImg = new Image("Explosion1.png", 4);
	pGoExplosion->AddComponent<Image>(pImg);
	pGoExplosion->GetComponent<Image>()->SetNativeSize();

	Transform* explosionTrs = &pGoExplosion->transform;
	explosionTrs->scale.Set(2, 2);

	explosionTrs->localPosition.x = this->transform->localPosition.x;
	explosionTrs->localPosition.y = this->transform->localPosition.y;
	explosionTrs->localPosition.x += this->transform->size.x * this->transform->scale.x / 2;
	explosionTrs->localPosition.x -= explosionTrs->size.x * explosionTrs->scale.x / 2;
	explosionTrs->localPosition.y += this->transform->size.y * this->transform->scale.y / 2;
	explosionTrs->localPosition.y -= explosionTrs->size.y * explosionTrs->scale.y / 2;

	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);

	Explode *explode = new Explode();
	pGoExplosion->AddComponent<Explode>(explode);
	AudioPlayer::GetInstance()->PlaySound("Explosion.wav");
}
