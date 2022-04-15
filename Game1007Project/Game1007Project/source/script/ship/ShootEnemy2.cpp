#include "ShootEnemy2.h"
#include "tools.h"

void ShootEnemy2::Init()
{
	m_pImg = this->gameObject->GetComponent<Image>();
}

void ShootEnemy2::Attack()
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

void ShootEnemy2::Move()
{
	int moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	transform->localPosition.x += .5;
}

void ShootEnemy2::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->localPosition, &camPos.localPosition);

	if (camPos.localPosition.x < -100)
		GameObjectManager::GetInstance()->PopGameObject(gameObject);

	if (camPos.localPosition.x > MainGame::screenW)
		return;

	Attack();
	Move();
}