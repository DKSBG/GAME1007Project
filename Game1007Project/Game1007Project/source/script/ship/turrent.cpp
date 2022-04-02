#include "reactableItem.h"
#include "tools.h"

void Turret::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->position, &camPos.position);

	if (camPos.position.x < -100)
	{
		GameObjectManager::GetInstance()->PopGameObject(gameObject);
	}

	if (camPos.position.x > MainGame::screenW)
	{
		return;
	}

	m_cdTimer -= Game::deltaTime;
	if (m_cdTimer <= 0)
	{
		Vector2 pos;
		ReactAttribute rectAttr;
		ItemAttribute attr;
		Transform trs;
		attr.atk = 1;
		attr.hp = 1;
		attr.speed = 400;
		attr.vector.Set(-1, -1);
		rectAttr.camp = Fiction::Enemy;
		rectAttr.reactValue = -attr.atk;
		rectAttr.target = ReactTarget::EnemyOnly;
		rectAttr.type = ReactType::HP;
		trs.position.Set(transform->position);
		m_shooting->Fire(trs, attr, rectAttr, "turretBullet.xml");
		m_cdTimer = m_attackCD;
	}
}

void Turret::Init()
{
	itemAttribute.hp = 1;
	itemAttribute.speed = 200;
	itemAttribute.atk = 1;
	itemAttribute.vector.Set(0, 0);

	reactAttrbute.camp = Fiction::Enemy;
	reactAttrbute.reactValue = -itemAttribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_shooting = (ShootStrategy*) new SingleLineShooting();
	m_attackCD = 750;
	m_pImg = this->gameObject->GetComponent<Image>();
}