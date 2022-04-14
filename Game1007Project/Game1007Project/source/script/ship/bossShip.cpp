#include "bossShip.h"
#include "tools.h"
#include "game.h"
#include "dataParser.h"
#include "explode.h"
#include "audioPlayer.h"

void BossShip::Update() 
{

	Vector2 camPos;
	GetCamPosition(m_pImg->GetCanvas()->GetCamera(), this->transform->globalPosition, &camPos);
	if (camPos.x > 500 && !m_start)
	{
		return;
	}
	else 
	{
		m_start = true;
		m_lastCamPosX = camPos.x;
	}

	if (m_isActing == false) 
	{
		m_isActing = true;

		if (m_currentIndex != 0 && m_currentIndex != 3)
		{
			m_currentIndex = 0;
			m_cdTime = 1500;
			m_cdTimer = m_cdTime;
		}
		else
			m_currentIndex = rand() % 3 + 1;
		m_actionCount = 0;
		std::cout << m_currentIndex << std::endl;
	}
	else 
	{
		float hpRate = itemAttribute.hp / m_maxHp;
		switch(m_currentIndex)
		{
		case 0:
			Idle();
			break;
		case 1:
			if (hpRate > 0.75) 
			{
				m_actionTimes = 3;
				m_basicGun->SetPiece(3);
			}
			else if (hpRate > 0.5) 
			{
				m_actionTimes = 4;
				m_basicGun->SetPiece(5);
			}
			else if (hpRate > 0.25)
			{
				m_actionTimes = 5;
				m_basicGun->SetPiece(7);
			}
			else
			{
				m_actionTimes = 6;
				m_basicGun->SetPiece(9);
			}
			m_cdTime = 160;
			itemAttribute.speed = 500;
			Fire();
			break;
		case 2:
			if (hpRate > 0.75)
			{
				m_actionTimes = 3;
				m_cdTime = 100;
			}
			else if (hpRate > 0.5)
			{
				m_actionTimes = 5;
				m_cdTime = 60;
			}
			else if (hpRate > 0.25)
			{
				m_actionTimes = 7;
				m_cdTime = 40;
			}
			else
			{
				m_actionTimes = 9;
				m_cdTime = 10;
			}

			m_actionTimes = 5;
			m_cdTime = 75;
			itemAttribute.speed = 500;

			CallShip();
			break;
		case 3:
			m_actionTimes = 4;
			m_cdTime = 50;
			itemAttribute.speed = 1000;
			MMove();
			break;
		}
	}

}
	
void BossShip::Init()
{
	srand(time(0));
	m_pImg = this->gameObject->GetComponent<Image>();
	m_pCam = m_pImg->GetCanvas()->GetCamera();
	m_maxHp = itemAttribute.hp;

	if (m_basicGun == NULL) 
	{
		GameObject* pGo = PrefabParser::GetInstance()->Parser("enemyGun1.xml");
		pGo->SetParent(gameObject);
		m_basicGun = pGo->GetComponent<Gun>();
		m_basicGun->SetCDTime(150);
		ItemAttribute attribute;
		m_basicGun->GetItemAttribute(&attribute);
		m_basicGun->SetVector(attribute.vector);
		m_basicGun->SetSpeed(250);
		m_basicGun->SetPiece(5);
		pGo->transform.localPosition.Set(-5, gameObject->transform.GetHeight() * 8 / 9);
	}
}

void BossShip::Fire()
{
	Vector2 camPos;
	Vector2 targetPos;
	targetPos.x = MainGame::screenW * 2 / 3;
	targetPos.y = MainGame::screenH / 2 - transform->GetHeight() / 2;
	GetCamPosition(m_pCam, this->transform->localPosition, &camPos);

	camPos.x = m_lastCamPosX;
	itemAttribute.vector.x = targetPos.x - camPos.x;
	itemAttribute.vector.y = targetPos.y - camPos.y;

	if (itemAttribute.vector.x * itemAttribute.vector.x + itemAttribute.vector.y * itemAttribute.vector.y > 200)
	{
		int moveX, moveY;
		GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);

		camPos.x += moveX;
		camPos.y += moveY;
	}
	else 
	{
		m_cdTimer -= Game::deltaGameTime;

		camPos.x = targetPos.x;
		camPos.y = targetPos.y;

		if (m_cdTimer <= 0) 
		{
			m_basicGun->Fire();
			m_cdTimer = m_cdTime;
			m_actionCount++;
		}

		if (m_actionCount > m_actionTimes)
			m_isActing = false;
	}

	m_lastCamPosX = camPos.x;
	GetRealPosition(m_pCam, camPos, &this->transform->localPosition);
}

void BossShip::CallShip()
{
	Vector2 camPos;
	GetCamPosition(m_pCam, this->transform->localPosition, &camPos);
	Vector2 targetPos;
	targetPos.x = MainGame::screenW * 6 / 7;
	targetPos.y = MainGame::screenH / 2 - transform->GetHeight() / 2;

	camPos.x = m_lastCamPosX;
	itemAttribute.vector.x = targetPos.x - camPos.x;
	itemAttribute.vector.y = targetPos.y - camPos.y;

	if (itemAttribute.vector.x * itemAttribute.vector.x + itemAttribute.vector.y * itemAttribute.vector.y > 100)
	{
		int moveX, moveY;
		GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);

		camPos.x += moveX;
		camPos.y += moveY;
	}
	else
	{
		m_cdTimer -= Game::deltaGameTime;
		int base = (m_actionTimes / 2) - (m_actionTimes % 2);

		camPos.x = targetPos.x;
		camPos.y = targetPos.y;

		if (m_cdTimer <= 0)
		{
			Vector2 tempPos;
			GameObject* go = PrefabParser::GetInstance()->Parser("boostEnemy.xml");
			tempPos.x = camPos.x;
			tempPos.y = (MainGame::screenH* 2 / 5) + (m_actionCount - base) * (MainGame::screenH / 10);
			GetRealPosition(m_pCam, tempPos, &go->transform.localPosition);

			m_cdTimer = m_cdTime;
			m_actionCount++;
		}

		if (m_actionCount > m_actionTimes)
			m_isActing = false;
	}

	m_lastCamPosX = camPos.x;
	GetRealPosition(m_pCam, camPos, &this->transform->localPosition);
}

void BossShip::Idle()
{
	m_cdTime = 200;
	m_cdTimer -= Game::deltaGameTime;

	Vector2 camPos;
	GetCamPosition(m_pCam, this->transform->localPosition, &camPos);
	camPos.x = m_lastCamPosX;

	if (m_cdTimer <= 0)
	{
		m_isActing = false;
	}

	m_lastCamPosX = camPos.x;
	GetRealPosition(m_pCam, camPos, &this->transform->localPosition);
}

void BossShip::MMove()
{
	Vector2 camPos;
	Vector2 pathNode;
	GetCamPosition(m_pCam, this->transform->localPosition, &camPos);

	camPos.x = m_lastCamPosX;

	switch (m_actionCount) 
	{
	case 0:
		pathNode.x = MainGame::screenW *2 / 3;
		pathNode.y = 0;
		break;
	case 1:
		pathNode.x = MainGame::screenW / 3;
		pathNode.y = MainGame::screenH * 1 / 4 - transform->GetHeight();
		break;
	case 2:
		pathNode.x = MainGame::screenW / 2;
		pathNode.y = MainGame::screenH / 2 - transform->GetHeight();
		break;
	case 3:
		pathNode.x = MainGame::screenW / 3;
		pathNode.y = MainGame::screenH * 3 / 4 - transform->GetHeight();
		break;
	case 4:
		pathNode.x = MainGame::screenW * 2 / 3;
		pathNode.y = MainGame::screenH - transform->GetHeight();
		break;
	}

	itemAttribute.vector.x = pathNode.x - camPos.x;
	itemAttribute.vector.y = pathNode.y - camPos.y;

	if (itemAttribute.vector.x * itemAttribute.vector.x + itemAttribute.vector.y * itemAttribute.vector.y > 100)
	{
		int moveX, moveY;
		GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);
		camPos.x += moveX;
		camPos.y += moveY;
		m_cdTimer = m_cdTime;
	}
	else
	{
		m_cdTimer -= Game::deltaGameTime;
		int base = (m_actionTimes / 2) - (m_actionTimes % 2);

		camPos.x = pathNode.x;
		camPos.y = pathNode.y;

		if (m_cdTimer <= 0)
		{
			m_cdTimer = m_cdTime;
			m_actionCount++;
		}

		if (m_actionCount > m_actionTimes)
			m_isActing = false;
	}


	m_lastCamPosX = camPos.x;
	GetRealPosition(m_pCam, camPos, &this->transform->localPosition);
}


void BossShip::OnExplode()
{
	Image* pImg;
	GameObject* pGoExplosion = new GameObject();
	pImg = new Image("Explosion1.png", 4);
	pGoExplosion->AddComponent<Image>(pImg);
	pGoExplosion->GetComponent<Image>()->SetNativeSize();

	Transform* explosionTrs = &pGoExplosion->transform;
	explosionTrs->scale.Set(5, 5);

	explosionTrs->localPosition.x = this->transform->localPosition.x;
	explosionTrs->localPosition.y = this->transform->localPosition.y;
	explosionTrs->localPosition.x += this->transform->size.x * this->transform->scale.x / 2;
	explosionTrs->localPosition.x -= explosionTrs->size.x * explosionTrs->scale.x / 2;
	explosionTrs->localPosition.y += this->transform->size.y * this->transform->scale.y / 2;
	explosionTrs->localPosition.y -= explosionTrs->size.y * explosionTrs->scale.y / 2;

	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);

	Explode* explode = new Explode();
	pGoExplosion->AddComponent<Explode>(explode);
	AudioPlayer::GetInstance()->PlaySound("Explosion.wav");
}
