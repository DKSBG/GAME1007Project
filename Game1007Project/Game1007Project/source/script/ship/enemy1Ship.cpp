#include "reactableItem.h"
#include "tools.h"

void Enemy1Ship::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->position, &camPos.position);

	if (camPos.position.x < -100) 
	{
		GameObjectManager::GetInstance()->PopGameObject(gameObject);
	}
		
	if(camPos.position.x > MainGame::screenW)
	{
		return;
	}

	m_cdTimer -= Game::deltaTime;

	int moveX, moveY;
	GetMovePixel(attribute.vector, attribute.speed, &moveX, &moveY);
	transform->position.x += moveX;

	if ((transform->position.y + moveY <= 0 && moveY < 0) ||
		(transform->position.y + moveY + (transform->size.y * transform->scale.y) >= Game::screenH / 2 && moveY > 0)) 
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
		rectAttr.camp = Fiction::Enemy;
		rectAttr.reactValue = -attr.atk;
		rectAttr.target = ReactTarget::EnemyOnly;
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

	reactAttrbute.camp = Fiction::Enemy;
	reactAttrbute.reactValue = - attribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_shooting = (ShootStrategy*) new SingleLineShooting();
	m_attackCD = 500;
	m_pImg = this->gameObject->GetComponent<Image>();
}