#include "playerShip.h"
#include "tools.h"
#include "gun.h"
#include "dataParser.h"

void PlayerShip::Init()
{
	m_pImg = this->gameObject->GetComponent<Image>();
	m_pCam = m_pImg->GetCanvas()->GetCamera();
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

	m_lastCamPosX = camPos.x;

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

	GetRealPosition(m_pCam, camPos, &this->transform->localPosition);
}

void PlayerShip::Update()
{
	Move();
	Attack();
}