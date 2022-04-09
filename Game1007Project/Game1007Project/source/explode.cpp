#include "explode.h"
#include "game.h"


void Explode::Update() 
{
	m_explodeTimer -= MainGame::deltaGameTime;
	if (m_explodeTimer < 0) 
	{
		GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
	}
}
