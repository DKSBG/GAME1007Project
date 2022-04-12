#include "reactableItem.h"
#include "tools.h"
#include "audioPlayer.h"
#include "turret.h"

void Turret::Init()
{
	itemAttribute.hp = 1;
	itemAttribute.speed = 200;
	itemAttribute.atk = 1;
	itemAttribute.vector.Set(0, 0);

	reactAttrbute.fiction = Fiction::Enemy;
	reactAttrbute.reactValue = -itemAttribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;
	m_pImg = this->gameObject->GetComponent<Image>();
}

void Turret::Attack() 
{
	if (m_pGun == NULL)
	{
		for (auto child : gameObject->GetChildren())
		{
			m_pGun = child->GetComponent<Gun>();
			if (m_pGun != NULL)
				break;
		}
	}
	else
	{
		m_pGun->Fire();
	}
}

void Turret::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->localPosition, &camPos.localPosition);
	if (camPos.localPosition.x < -100)
	{
		GameObjectManager::GetInstance()->PopGameObject(gameObject);
	}

	if (camPos.localPosition.x > MainGame::screenW)
	{
		return;
	}

	Attack();
}

