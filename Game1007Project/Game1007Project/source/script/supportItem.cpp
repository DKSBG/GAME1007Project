#include "supportItem.h"
#include "explode.h"
#include "audioPlayer.h"

void PlayerProtector::SpecificReact(ReactableItem* giver)
{
	if (giver->gameObject->transform.GetWidth() > 30)
		return;

	Image* pImg;
	GameObject* pGoExplosion = new GameObject();
	pImg = new Image("Explosion1.png", 4);
	pGoExplosion->AddComponent<Image>(pImg);
	pGoExplosion->GetComponent<Image>()->SetNativeSize();

	Transform* explosionTrs = &pGoExplosion->transform;
	explosionTrs->scale.Set(1, 1);

	explosionTrs->localPosition.x = giver->gameObject->transform.globalPosition.x;
	explosionTrs->localPosition.y = giver->gameObject->transform.globalPosition.y;

	pGoExplosion->SetParent(gameObject);
	Explode* explode = new Explode();
	pGoExplosion->AddComponent<Explode>(explode);
	AudioPlayer::GetInstance()->PlaySound("Explosion.wav");
}
