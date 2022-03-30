#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void SingleLineShooting::Fire(Transform* attacker, ItemAttribute attr, ReactAttribute reactAttr)
{
	Image* pImg;
	GameObject* bullet = new GameObject();
	pImg = new Image("MainShipBullet.png", 4);
	bullet->AddComponent<Image>(pImg);
	bullet->GetComponent<Image>()->SetNativeSize();

	Transform* pBulletTransform = &bullet->transform;
	pBulletTransform->scale.Set(2, 2);
	pBulletTransform->position.x = attacker->position.x;
	pBulletTransform->position.y = attacker->position.y;
	if (attr.vector->x > 0)
		pBulletTransform->position.x += attacker->size.x * attacker->scale.x;
	else
		pBulletTransform->position.x -= pBulletTransform->size.x * pBulletTransform->scale.x;
	pBulletTransform->position.y += attacker->size.y * attacker->scale.y / 2;
	pBulletTransform->position.y -= pBulletTransform->size.y * pBulletTransform->scale.y / 2;

	StraightProjectile* bulletScript = new StraightProjectile();
	bulletScript->attribute.atk = attr.atk;
	bulletScript->attribute.hp = attr.hp;
	bulletScript->attribute.speed = attr.speed;
	bulletScript->attribute.vector = new Vector2(attr.vector->x, attr.vector->y);
	bulletScript->reactAttrbute.camp = reactAttr.camp;
	bulletScript->reactAttrbute.reactValue = reactAttr.reactValue;
	bulletScript->reactAttrbute.target = reactAttr.target;
	bulletScript->reactAttrbute.type = reactAttr.type;
	bullet->AddComponent<ReactableItem>(bulletScript);
	bullet->AddComponent<Collider>(new Collider());
}