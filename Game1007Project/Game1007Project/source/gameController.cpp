#include "gameController.h"
#include "game.h"
#include "audioPlayer.h"

void GameController::Init() 
{
	m_pMainCam = CameraManager::GetInstance()->GetCamera("MainCam");
	AudioPlayer::GetInstance()->PlayMusic("level1.ogg");
}

void GameController::Update() 
{
	m_pMainCam->transform.position.x += (float)100 / 1000 * MainGame::deltaGameTime;
}
