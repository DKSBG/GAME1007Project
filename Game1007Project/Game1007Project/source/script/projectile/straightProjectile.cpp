#include "reactableItem.h"
#include "tools.h"
#include "image.h"
#include "gameObject.h"

void StraightProjectile::Update()
{
	Transform camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->globalPosition, &camPos.globalPosition);

	if(camPos.globalPosition.x <= -transform->GetWidth() || camPos.globalPosition.x >= MainGame::screenW ||
		camPos.globalPosition.y <= -transform->GetHeight()  || camPos.globalPosition.y >= MainGame::screenH)
	{
		GameObjectManager::GetInstance()->PopGameObject(gameObject);
	}

	float moveX, moveY;
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
	this->transform->localPosition.y += moveY;
	this->transform->localPosition.x += moveX;
}


