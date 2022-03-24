#include "reactableItem.h"
#include "tools.h"
#include "image.h"

void StraightProjectile::Update()
{
	int moveX, moveY;
	GetMovePixel(attribute.vector, attribute.speed, &moveX, &moveY);
	this->transform->position->y += moveY;
	this->transform->position->x += moveX;
}


