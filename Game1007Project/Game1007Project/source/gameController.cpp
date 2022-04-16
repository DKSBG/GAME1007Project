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

	GameObject* result = new GameObject();
	m_resultPage = new Image("win.png", 10);
	result->AddComponent<Image>(m_resultPage);
	result->transform.size.Set(MainGame::screenW, MainGame::screenH);
	result->isActive = false;
}

void GameController::Update() 
{
	m_pMainCam->transform.globalPosition.x += (float)100 / 1000 * MainGame::deltaGameTime;
	if(m_isResult)
		m_resultDelay -= MainGame::deltaGameTime;

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
		else 
		{
			if (m_isResult == false)
			{
				AudioPlayer::GetInstance()->PlayMusic("credits.ogg");
				m_isResult = true;
			}

			if (m_resultDelay < 0)
			{
				m_resultPage->ChangeSprite("lose.png");
				m_resultPage->gameObject->isActive = true;
				MainGame::GetInstance()->Pause();
			}
		}
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
			}
			else 
			{
				ui->SetBossHP(((float)m_boss->itemAttribute.hp) / m_bossMaxHp);
				if (m_boss->itemAttribute.hp == 0)
				{
					if (m_isResult == false) 
					{
						AudioPlayer::GetInstance()->PlayMusic("start.ogg");
						m_isResult = true;
					}

					if (m_resultDelay < 0) 
					{
						m_resultPage->ChangeSprite("win.png");
						m_resultPage->gameObject->isActive = true;
						MainGame::GetInstance()->Pause();
					}
				}
			}
		}
		else 
		{
			ui->SetProgressPosition(m_pMainCam->transform.globalPosition.x /m_mapWeight);
		}
	}
}
