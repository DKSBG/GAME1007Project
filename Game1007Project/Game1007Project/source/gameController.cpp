#include "gameController.h"
#include "game.h"
#include "audioPlayer.h"
#include "dataParser.h"
#include "playerUI.h"
#include "SDL.h"

PlayerUI* ui;

void GameController::Init() 
{
	m_pMainCam = CameraManager::GetInstance()->GetCamera("MainCam");
	AudioPlayer::GetInstance()->PlayMusic("level1.ogg");
	GameObject* go = new GameObject();
	ui = new PlayerUI();
	go->AddComponent<PlayerUI>(ui);

	m_player = (Ship*) PrefabParser::GetInstance()->Parser("mainShip.xml")->GetComponent<ReactableItem>();
	m_player->transform->localPosition.y = MainGame::screenH/2 - m_player->transform->GetHeight() / 2;
	m_player->transform->localPosition.x = m_pMainCam->transform.globalPosition.x + 30;
}

void GameController::Update() 
{
	m_pMainCam->transform.globalPosition.x += (float)100 / 1000 * MainGame::deltaGameTime;

	//int mouseX, mouseY;
	//SDL_GetMouseState(&mouseX, &mouseY);
	//std::cout << mouseX << " - " << mouseY << std::endl;
	if (m_player->itemAttribute.hp <= 0) 
	{
		if (MainGame::GetInstance()->GetPlayerInfo()->playTimes > 0) 
		{
			m_player = (Ship*)PrefabParser::GetInstance()->Parser("mainShip.xml")->GetComponent<ReactableItem>();
			m_player->transform->localPosition.y = MainGame::screenH / 2 - m_player->transform->GetHeight() / 2;
			m_player->transform->localPosition.x = m_pMainCam->transform.globalPosition.x + 30;
			MainGame::GetInstance()->GetPlayerInfo()->playTimes--;
			ui->SetUIPlayTimes(MainGame::GetInstance()->GetPlayerInfo()->playTimes);
		}
		//else 
		//{
		//	Game::GetInstance()->Pause();
		//}
	}
	else 
	{
		if (m_pMainCam->transform.globalPosition.x > m_mapWeight)
		{
			ui->UIProgressEnable(false);
			if (m_boss == NULL) 
			{
				AudioPlayer::GetInstance()->PlayMusic("boss.ogg");
				m_boss = (BossShip*)PrefabParser::GetInstance()->Parser("bossShip.xml")->GetComponent<ReactableItem>();
				m_boss->gameObject->transform.localPosition.x = m_pMainCam->transform.globalPosition.x + MainGame::screenW;
				m_boss->gameObject->transform.localPosition.y = MainGame::screenH / 2 - m_boss->transform->GetHeight()/2;
				m_bossMaxHp = m_boss->itemAttribute.hp;
				ui->UIBossHPEnable(true);
				if (m_boss->itemAttribute.hp == 0)
				{
					//GameObjectManager::GetInstance()->PopAllGameObject();
					//CameraManager::GetInstance()->ClearCamera();
					//SceneLoader::GetInstance()->Load("Scene1.xml");
				}
			}
			else 
			{
				ui->SetBossHP(((float)m_boss->itemAttribute.hp) / m_bossMaxHp);
			}

		}
		else 
		{
			ui->SetProgressPosition(m_pMainCam->transform.globalPosition.x /m_mapWeight);
		}
	}
}
