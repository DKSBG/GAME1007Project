#include "reactableItem.h"
#include "tools.h"
#include "image.h"
#include "dataParser.h"


void SingleLineShooting::Fire(const Transform attacker, ItemAttribute attr, ReactAttribute reactAttr, std::string bullet)
{
	Image* pImg;
	GameObject* bulletObject = PrefabParser::GetInstance()->Parser(bullet);
	Transform* pBulletTransform = &bulletObject->transform;
	pBulletTransform->position.Set(attacker.position);
	ReactableItem* bulletScript = bulletObject->GetComponent<ReactableItem>();
	bulletScript->itemAttribute.atk = attr.atk;
	bulletScript->itemAttribute.hp = attr.hp;
	bulletScript->itemAttribute.speed = attr.speed;
	bulletScript->itemAttribute.vector.Set(attr.vector.x, attr.vector.y);
	bulletScript->reactAttrbute.camp = reactAttr.camp;
	bulletScript->reactAttrbute.reactValue = reactAttr.reactValue;
	bulletScript->reactAttrbute.target = reactAttr.target;
	bulletScript->reactAttrbute.type = reactAttr.type;
}