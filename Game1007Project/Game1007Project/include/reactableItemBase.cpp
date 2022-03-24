#pragma once
#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void ReactableItem::Init() {};

void ReactableItem::Update() {};

void ReactableItem::OnCollide(GameObject* go) 
{
	ReactableItem* giver = go->GetComponent<ReactableItem>();
	if (giver == NULL)
		return;
	if (giver->reactAttrbute.camp == reactAttrbute.camp && giver->reactAttrbute.target == EnemyOnly)
		return;
	Reacting(giver->reactAttrbute);
};

void ReactableItem::Reacting(ReactAttribute reactAttr)
{
	int* targetValue = NULL;

	switch (reactAttr.type)
	{
	case ReactType::HP:
		targetValue = &attribute.hp;
		break;
	case ReactType::Speed:
		targetValue = &attribute.speed;
		break;
	case ReactType::Atk:
		targetValue = &attribute.atk;
		break;
	default:
		break;
	}

	if (targetValue != NULL)
		*targetValue += reactAttr.reactValue;

	if (attribute.hp <= 0)
		OnDie();
	SpecificReact(reactAttr);
}

void Projectile::Update() {}
void Projectile::OnDie() 
{
	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}
void Projectile::SpecificReact(ReactAttribute giverAttr) {}

void StraightProjectile::Update() 
{
	int moveX, moveY;
	GetMovePixel(attribute.vector, attribute.speed, &moveX, &moveY);
	this->transform->position->y += moveY;
	this->transform->position->x += moveX;
}

void SingleLineShooting::Fire(Transform* attacker, ItemAttribute attr, ReactAttribute reactAttr)
{
	Image* pImg;
	GameObject* bullet = new GameObject();
	pImg = new Image("MainShipBullet.png", 4);
	bullet->AddComponent<Image>(pImg);
	bullet->GetComponent<Image>()->SetNativeSize();

	Transform* bulletTransform = bullet->transform;
	bulletTransform->scale = new Vector2(2, 2);
	bulletTransform->position->x = attacker->position->x;
	bulletTransform->position->y = attacker->position->y;
	if (attr.vector->x > 0)
		bulletTransform->position->x += attacker->size->x * attacker->scale->x;
	else
		bulletTransform->position->x -= attacker->size->x * attacker->scale->x;
	bulletTransform->position->y += attacker->size->y * attacker->scale->y / 2;
	bulletTransform->position->y -= bulletTransform->size->y * bulletTransform->scale->y / 2;

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

