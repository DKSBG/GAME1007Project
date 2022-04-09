#include "reactableItem.h"
#include "tools.h"
#include "audioPlayer.h"

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
	m_shooting->bullet = "turretBullet.xml";
	m_shooting->fireSound = "EnemyLaser.mp3";

	m_attackCD = 750;
	m_pImg = this->gameObject->GetComponent<Image>();
}

void Turret::Attack() 
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
		attr.vector.Set(-1, -1);
		rectAttr.camp = Fiction::Enemy;
		rectAttr.reactValue = -attr.atk;
		rectAttr.target = ReactTarget::EnemyOnly;
		rectAttr.type = ReactType::HP;
		trs.position.Set(transform->position);
		m_shooting->Fire(trs, attr, rectAttr);
		m_cdTimer = m_attackCD;
	}
}

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

	Attack();
}

