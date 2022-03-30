#include "reactableItem.h"
#include "tools.h"

void Enemy1Ship::Update()
{
	m_cdTimer -= Game::deltaTime;

	int moveX, moveY;
	GetMovePixel(attribute.vector, attribute.speed, &moveX, &moveY);
	transform->position.x += moveX;

	if (transform->position.y + moveY <= 0 ||
		transform->position.y + moveY + (transform->size.y * transform->scale.y) >= Game::screenH/2)
	{
		moveY = -moveY;
		attribute.vector->y = -attribute.vector->y;
	}
	transform->position.y += moveY;

	if (m_cdTimer <= 0)
	{
		Vector2 pos;
		ReactAttribute rectAttr;
		ItemAttribute attr;
		attr.atk = 1;
		attr.hp = 1;
		attr.speed = 400;
		attr.vector = new Vector2(-1, 0);
		rectAttr.camp = Camp::Enemy;
		rectAttr.reactValue = -attr.atk;
		rectAttr.target = ReactCamp::EnemyOnly;
		rectAttr.type = ReactType::HP;

		m_shooting->Fire(this->transform, attr, rectAttr);
		m_cdTimer = m_attackCD;
	}
}

void Enemy1Ship::Init()
{
	attribute.hp = 1;
	attribute.speed = 200;
	attribute.atk = 1;
	attribute.vector = new Vector2(0, -1);

	reactAttrbute.camp = Camp::Enemy;
	reactAttrbute.reactValue = - attribute.atk;
	reactAttrbute.target = ReactCamp::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_shooting = (ShootStrategy*) new SingleLineShooting();
	m_attackCD = 500;
}