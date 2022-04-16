#pragma once
#include "reactableItem.h"

class SupportItem : public ReactableItem
{
	void SpecificReact(ReactableItem* giver) {}
	void OnDie() {}
};

class PlayerProtector : public ReactableItem
{
	void SpecificReact(ReactableItem* giver);
	void OnDie() {}
};