#include "reactableItem.h"
#include "tools.h"

void PlayerShip::Init()
{
	itemAttribute.hp = 1;
	itemAttribute.speed = 200;
	itemAttribute.atk = 1;
	itemAttribute.vector.Set(0, 0);

	reactAttrbute.camp = Fiction::Ally;
	reactAttrbute.reactValue = - itemAttribute.atk;
	reactAttrbute.target = ReactTarget::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_shooting = (ShootStrategy*) new SingleLineShooting();
	m_pImg = this->gameObject->GetComponent<Image>();
	m_pCam = m_pImg->GetCanvas()->GetCamera();
}

void PlayerShip::Update()
{
	int moveX, moveY;
	itemAttribute.vector.y = 0;
	itemAttribute.vector.x = 0;

	m_cdTimer -= Game::deltaTime;

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

	if (m_KeyboardStates[SDL_SCANCODE_O])
	{
		delete m_shooting;
		m_shooting = (ShootStrategy*) new SingleLineShooting();
	}

	if (m_KeyboardStates[SDL_SCANCODE_P])
	{
		delete m_shooting;
		m_shooting = (ShootStrategy*) new SingleLineShooting();
	}

	GetMovePixel(&itemAttribute.vector, itemAttribute.speed, &moveX, &moveY);

	Transform camPos;
	GetCamPosition(m_pCam, this->transform->position, &camPos.position);

	camPos.position.x += moveX + (m_lastCamPosX - camPos.position.x);
	camPos.position.y += moveY;

	m_lastCamPosX = camPos.position.x;

	if (camPos.position.y < 0)
	{
		camPos.position.y = 0;
	}

	if (camPos.position.y + transform->size.y * transform->scale.y > Game::screenH)
	{
		camPos.position.y = Game::screenH - transform->size.y * transform->scale.y;
	}

	if (camPos.position.x < 0)
	{
		camPos.position.x = 0;
	}

	if (camPos.position.x + transform->size.x * transform->scale.x > Game::screenW)
	{
		camPos.position.x = Game::screenW - transform->size.x * transform->scale.x;
	}

	GetRealPosition(m_pCam, camPos.position, &this->transform->position);

	if (m_KeyboardStates[SDL_SCANCODE_SPACE])
	{
		if (m_cdTimer <= 0)
		{
			Vector2 pos;
			ReactAttribute rectAttr;
			ItemAttribute attr;
			Transform trs;
			attr.atk = 1;
			attr.hp = 1;
			attr.speed = 400;
			attr.vector.Set(1, 0);
			rectAttr.camp = Fiction::Ally;
			rectAttr.reactValue = -attr.atk;
			rectAttr.target = ReactTarget::EnemyOnly;
			rectAttr.type = ReactType::HP;
			trs.Clone(*this->transform);
			trs.position.x += transform->size.x * transform->scale.x;
			trs.position.x += transform->size.y * transform->scale.y;
			m_shooting->Fire(trs, attr, rectAttr, "mainShipBullet.xml");
			m_cdTimer = m_attackCD;
		}
	}
}