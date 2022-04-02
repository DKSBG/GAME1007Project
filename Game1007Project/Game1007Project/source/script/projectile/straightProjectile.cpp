#include "reactableItem.h"
#include "tools.h"
#include "image.h"
#include "gameObject.h"

void StraightProjectile::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->position, &camPos.position);

	if(camPos.position.x <= -10 || camPos.position.x >= MainGame::screenW || 
		camPos.position.y <= -10 || camPos.position.y >= MainGame::screenH)
	{
		GameObjectManager::GetInstance()->PopGameObject(gameObject);
	}

	int moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	this->transform->position.y += moveY;
	this->transform->position.x += moveX;
}


