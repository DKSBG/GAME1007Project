#include "gameController.h"
#include "game.h"

void GameController::Init() 
{
	m_pMainCam = CameraManager::GetInstance()->GetCamera("MainCam");
}

void GameController::Update() 
{
	m_pMainCam->transform.position.x += (float)100 / 1000 * MainGame::deltaTime;
}
