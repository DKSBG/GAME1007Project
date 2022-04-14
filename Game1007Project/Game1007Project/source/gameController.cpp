#include "gameController.h"
#include "game.h"
#include "audioPlayer.h"
#include "dataParser.h"

void GameController::Init() 
{
	m_pMainCam = CameraManager::GetInstance()->GetCamera("MainCam");
	AudioPlayer::GetInstance()->PlayMusic("level1.ogg");
}

void GameController::Update() 
{
	m_pMainCam->transform.globalPosition.x += (float)100 / 1000 * MainGame::deltaGameTime;
	if (m_boss == NULL) 
	{
		m_boss = (BossShip*) PrefabParser::GetInstance()->Parser("bossShip.xml")->GetComponent<ReactableItem>();
		m_boss->gameObject->transform.localPosition.x = m_pMainCam->transform.globalPosition.x + 1000;
		m_boss->gameObject->transform.localPosition.y = 200;
	}
	else 
	{
		if (m_boss->itemAttribute.hp == 0) 
		{
			GameObjectManager::GetInstance()->PopAllGameObject();
			CameraManager::GetInstance()->ClearCamera();
			SceneLoader::GetInstance()->Load("Scene1.xml");
		}

	}
}
