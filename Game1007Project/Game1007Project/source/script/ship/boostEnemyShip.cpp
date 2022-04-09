#include "reactableItem.h"
#include "tools.h"

void BoostEnemyShip::Move() 
{
	itemAttribute.speed += m_acceleration * MainGame::deltaGameTime / 1000;

	int moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	transform->position.x += moveX;
}

void BoostEnemyShip::Init()
{
	itemAttribute.hp = 1;
	itemAttribute.speed = 200;
	itemAttribute.atk = 1;
	itemAttribute.vector.Set(-1, 0);

	reactAttrbute.camp = Fiction::Enemy;
	reactAttrbute.reactValue = -itemAttribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_acceleration = 500;
	m_pImg = this->gameObject->GetComponent<Image>();
}

void BoostEnemyShip::Update()
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

	Move();
}