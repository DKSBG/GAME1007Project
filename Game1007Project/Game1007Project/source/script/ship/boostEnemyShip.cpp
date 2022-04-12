#include "boostEnemyShip.h"
#include "tools.h"

void BoostEnemyShip::Move() 
{
	itemAttribute.speed += acceleration * MainGame::deltaGameTime / 1000;

	int moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	transform->localPosition.x += moveX;
}

void BoostEnemyShip::Init()
{
	acceleration = 500;
	m_pImg = this->gameObject->GetComponent<Image>();
}

void BoostEnemyShip::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->globalPosition, &camPos.globalPosition);

	if (camPos.globalPosition.x < -100)
	{
		GameObjectManager::GetInstance()->PopGameObject(gameObject);
	}

	if (camPos.globalPosition.x > MainGame::screenW)
	{
		return;
	}

	Move();
}