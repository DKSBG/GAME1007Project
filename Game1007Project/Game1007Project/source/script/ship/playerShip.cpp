#include "playerShip.h"
#include "tools.h"
#include "gun.h"
#include "dataParser.h"
#include "audioPlayer.h"

void PlayerShip::Init()
{
	m_pImg = this->gameObject->GetComponent<Image>();
	m_pCam = m_pImg->GetCanvas()->GetCamera();
	Invincible();
}

void PlayerShip::Attack() 
{
	if (m_KeyboardStates[SDL_SCANCODE_SPACE])
	{
		if (m_pGun == NULL)
		{
			for (auto child : gameObject->GetChildren())
			{
				m_pGun = child->GetComponent<Gun>();
				if (m_pGun != NULL)
					break;
			}
		}

		if (m_pGun != NULL)
			m_pGun->Fire();
	}
}

void PlayerShip::Move() 
{
	int moveX, moveY;
	itemAttribute.vector.y = 0;
	itemAttribute.vector.x = 0;

	m_cdTimer -= Game::deltaGameTime;

	if (m_KeyboardStates[SDL_SCANCODE_LEFTBRACKET])
		transform->rotation--;
	else if (m_KeyboardStates[SDL_SCANCODE_RIGHTBRACKET])
		transform->rotation++;

	if (m_KeyboardStates[SDL_SCANCODE_F])
		m_pImg->isFlip = true;
	else if(m_KeyboardStates[SDL_SCANCODE_G])
		m_pImg->isFlip = false;

	if (m_KeyboardStates[SDL_SCANCODE_N] && m_pImg->alpah > 0)
		m_pImg->alpah--;
	else if (m_KeyboardStates[SDL_SCANCODE_M] && m_pImg->alpah < 255)
		m_pImg->alpah++;


	if (m_KeyboardStates[SDL_SCANCODE_W])
		itemAttribute.vector.y = -1;
	if (m_KeyboardStates[SDL_SCANCODE_S])
		itemAttribute.vector.y = 1;
	if (m_KeyboardStates[SDL_SCANCODE_A])
		itemAttribute.vector.x = -1;
	if (m_KeyboardStates[SDL_SCANCODE_D])
		itemAttribute.vector.x = 1;

	string spriteName = "MainShip.png";

	if (itemAttribute.vector.x <= 0)
	{
		if (itemAttribute.vector.y < 0)
			spriteName = "MainShipUp.png";
		if (itemAttribute.vector.y > 0)
			spriteName = "MainShipDown.png";
	}
	else
	{
		if (itemAttribute.vector.y < 0)
			spriteName = "MainShipUpForward.png";
		if (itemAttribute.vector.y > 0)
			spriteName = "MainShipDownForward.png";
	}

	m_pImg->ChangeSprite(spriteName);
	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);

	Vector2 camPos;
	GetCamPosition(m_pCam, this->transform->localPosition, &camPos);

	camPos.x += moveX + (m_lastCamPosX - camPos.x);
	camPos.y += moveY;

	if (camPos.y < 0)
	{
		camPos.y = 0;
	}

	if (camPos.y + transform->GetHeight() > Game::screenH)
	{
		camPos.y = Game::screenH - transform->GetHeight();
	}

	if (camPos.x < 0)
	{
		camPos.x = 0;
	}

	if (camPos.x + transform->GetWidth() > Game::screenW)
	{
		camPos.x = Game::screenW - transform->GetWidth();
	}

	m_lastCamPosX = camPos.x;
	GetRealPosition(m_pCam, camPos, &this->transform->localPosition);
}

void PlayerShip::Invincible() 
{
	if (m_protector == NULL) 
	{
		m_protector = PrefabParser::GetInstance()->Parser("protector.xml");
		m_protector->SetParent(gameObject);
		m_protector->transform.size.Set(transform->GetWidth(), transform->GetWidth());
		m_protector->transform.scale.Set(4, 4);
		m_protector->transform.localPosition.x = transform->GetWidth() / 2 - m_protector->transform.GetWidth() / 2 + 8;
		m_protector->transform.localPosition.y = transform->GetHeight() / 2 - m_protector->transform.GetHeight() / 2 + 5;
	}
	m_invincibleTimer = 1500;
	itemAttribute.hp = 10000;
	reactAttrbute.reactValue = 0;
}

void PlayerShip::SpecificReact(ReactableItem* giver)
{
	if (giver->reactAttrbute.type == ReactType::Follower) 
	{
		if (m_follower[0] == NULL) 
		{
			m_follower[0] = PrefabParser::GetInstance()->Parser("follower.xml");
			m_follower[0]->SetParent(gameObject);
			m_follower[0]->transform.localPosition.Set(0, -60);
			m_follower[0]->transform.globalPosition.Set(transform->globalPosition.x, transform->globalPosition.y - 60);
		}
		else if (m_follower[1] == NULL)
		{
			m_follower[1] = PrefabParser::GetInstance()->Parser("follower.xml");
			m_follower[1]->SetParent(gameObject);
			m_follower[1]->transform.localPosition.Set(0, 60);
			m_follower[1]->transform.globalPosition.Set(transform->globalPosition.x, transform->globalPosition.y + 60);
		}
		AudioPlayer::GetInstance()->PlaySound(-1, "Pickup_Coin.wav", 1, 10);
		GameObjectManager::GetInstance()->PopGameObject(giver->gameObject);
	}

	if (giver->reactAttrbute.type == ReactType::Piece) 
	{
		if (m_pGun == NULL)
		{
			for (auto child : gameObject->GetChildren())
			{
				m_pGun = child->GetComponent<Gun>();
				if (m_pGun != NULL)
					break;
			}
		}

		if (piece < 7) 
		{
			piece += 2;
			m_pGun->SetPiece(piece);
		}
		AudioPlayer::GetInstance()->PlaySound(-1, "Pickup_Coin.wav", 1, 10);
		GameObjectManager::GetInstance()->PopGameObject(giver->gameObject);
	}
}

void PlayerShip::Update()
{
	m_invincibleTimer -= MainGame::deltaGameTime;
	if (m_invincibleTimer < 0) 
	{
		m_protector->isActive = false;
		itemAttribute.hp = 1;
		reactAttrbute.reactValue = -1;
	}

	Move();
	Attack();
}


void Follower::Update() 
{
	Attack();
}

void Follower::Attack() 
{
	if (m_pGun == NULL)
	{
		for (auto child : gameObject->GetChildren())
		{
			m_pGun = child->GetComponent<Gun>();
			if (m_pGun != NULL)
				break;
		}
		m_pGun->SetCDTime(500);
	}
	else
	{
		m_pGun->Fire();
	}
}
