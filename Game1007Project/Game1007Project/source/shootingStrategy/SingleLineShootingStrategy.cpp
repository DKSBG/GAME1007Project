#include "reactableItem.h"
#include "tools.h"
#include "image.h"
#include "dataParser.h"
#include "audioPlayer.h"


void SingleLineShooting::Fire(const Transform attacker, ItemAttribute attr, ReactAttribute reactAttr)
{
	Image* pImg;
	GameObject* bulletObject = PrefabParser::GetInstance()->Parser(bullet);
	Transform* pBulletTransform = &bulletObject->transform;
	pBulletTransform->localPosition.Set(attacker.localPosition);
	ReactableItem* bulletScript = bulletObject->GetComponent<ReactableItem>();
	bulletScript->itemAttribute.atk = attr.atk;
	bulletScript->itemAttribute.hp = attr.hp;
	bulletScript->itemAttribute.speed = attr.speed;
	bulletScript->itemAttribute.vector.Set(attr.vector.x, attr.vector.y);
	bulletScript->reactAttrbute.fiction = reactAttr.fiction;
	bulletScript->reactAttrbute.reactValue = reactAttr.reactValue;
	bulletScript->reactAttrbute.target = reactAttr.target;
	bulletScript->reactAttrbute.type = reactAttr.type;

	AudioPlayer::GetInstance()->PlaySound(1, fireSound, 1, 2.0);
}