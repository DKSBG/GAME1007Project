#include "reactableItem.h"
#include "tools.h"
#include "audioPlayer.h"
#include "explode.h"
#include "audioPlayer.h"
#include "dataParser.h"

void Ship::OnDie()
{
	if (reactAttrbute.fiction == Fiction::Enemy)
	{
		int rand = std::rand() % 100;
		if (rand >= 10 && rand <= 15) 
		{
			AudioPlayer::GetInstance()->PlaySound("Randomize2.wav");
			PrefabParser::GetInstance()->Parser("pieceItem.xml")->transform.globalPosition.Set(transform->globalPosition.x, transform->globalPosition.y);
		}
			
		if (rand >= 75 && rand <= 80) 
		{
			AudioPlayer::GetInstance()->PlaySound("Randomize2.wav");
			PrefabParser::GetInstance()->Parser("followerItem.xml")->transform.globalPosition.Set(transform->globalPosition.x, transform->globalPosition.y);
		}
			
	}
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
