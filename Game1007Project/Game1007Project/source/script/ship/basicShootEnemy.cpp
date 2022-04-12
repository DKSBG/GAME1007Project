#include "basicShootEnemy.h"
#include "tools.h"

void BasicShootEnemy::Init()
{
	m_pImg = this->gameObject->GetComponent<Image>();
}

void BasicShootEnemy::Attack()
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

void BasicShootEnemy::Move()
{
	int moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	transform->localPosition.x += moveX;

	if ((transform->localPosition.y + moveY <= 0 && moveY < 0) ||
		(transform->localPosition.y + moveY + (transform->size.y * transform->scale.y) >= Game::screenH / 2 && moveY > 0))
	{
		moveY = -moveY;
		itemAttribute.vector.y = -itemAttribute.vector.y;
	}

	transform->localPosition.y += moveY;

}

void BasicShootEnemy::Update()
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