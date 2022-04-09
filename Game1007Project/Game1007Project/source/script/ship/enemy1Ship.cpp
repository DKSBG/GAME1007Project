#include "reactableItem.h"
#include "tools.h"
#include "audioPlayer.h"

void Enemy1Ship::Init()
{
	itemAttribute.hp = 1;
	itemAttribute.speed = 200;
	itemAttribute.atk = 1;
	itemAttribute.vector.Set(0, -1);

	reactAttrbute.camp = Fiction::Enemy;
	reactAttrbute.reactValue = -itemAttribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_shooting = (ShootStrategy*) new SingleLineShooting();
	m_shooting->bullet = "enemy1Bullet.xml";
	m_shooting->fireSound = "EnemyLaser.mp3";

	m_attackCD = 1000;
	m_pImg = this->gameObject->GetComponent<Image>();
}

void Enemy1Ship::Attack() 
{
	m_cdTimer -= Game::deltaGameTime;
	if (m_cdTimer <= 0)
	{
		Vector2 pos;
		ReactAttribute rectAttr;
		ItemAttribute attr;
		Transform trs;
		attr.atk = 1;
		attr.hp = 1;
		attr.speed = 400;
		attr.vector.Set(-1, 0);
		rectAttr.camp = Fiction::Enemy;
		rectAttr.reactValue = -attr.atk;
		rectAttr.target = ReactTarget::EnemyOnly;
		rectAttr.type = ReactType::HP;
		trs.position.Set(transform->position);
		trs.position.y += transform->size.y * transform->scale.y;
		m_shooting->Fire(trs, attr, rectAttr);
		m_cdTimer = m_attackCD;
	}
}

void Enemy1Ship::Move()
{
	int moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	transform->position.x += moveX;

	if ((transform->position.y + moveY <= 0 && moveY < 0) ||
		(transform->position.y + moveY + (transform->size.y * transform->scale.y) >= Game::screenH / 2 && moveY > 0))
	{
		moveY = -moveY;
		itemAttribute.vector.y = -itemAttribute.vector.y;
	}

	transform->position.y += moveY;

}

void Enemy1Ship::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->position, &camPos.position);

	if (camPos.position.x < -100)
		GameObjectManager::GetInstance()->PopGameObject(gameObject);

	if (camPos.position.x > MainGame::screenW)
		return;

	Attack();
	Move();
}