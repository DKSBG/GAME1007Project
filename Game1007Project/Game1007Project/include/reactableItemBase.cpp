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
	if (giver->reactAttrbute.camp == reactAttrbute.camp && giver->reactAttrbute.target == ReactTarget::EnemyOnly)
		return;
	Reacting(giver->reactAttrbute);
};

void ReactableItem::Reacting(ReactAttribute reactAttr)
{
	int* targetValue = NULL;

	switch (reactAttr.type)
	{
	case ReactType::HP:
		targetValue = &itemAttribute.hp;
		break;
	case ReactType::Speed:
		targetValue = &itemAttribute.speed;
		break;
	case ReactType::Atk:
		targetValue = &itemAttribute.atk;
		break;
	default:
		break;
	}

	if (targetValue != NULL)
		*targetValue += reactAttr.reactValue;

	if (itemAttribute.hp <= 0)
		OnDie();
	SpecificReact(reactAttr);
}
