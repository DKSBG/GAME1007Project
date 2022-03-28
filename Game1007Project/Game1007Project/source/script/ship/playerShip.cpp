#include "reactableItem.h"
#include "tools.h"

void PlayerShip::Init()
{
	attribute.hp = 1;
	attribute.speed = 200;
	attribute.atk = 1;
	attribute.vector = new Vector2(0, 0);

	reactAttrbute.camp = Camp::Ally;
	reactAttrbute.reactValue = - attribute.atk;
	reactAttrbute.target = ReactCamp::EnemyOnly;
	reactAttrbute.type = ReactType::HP;

	m_shooting = (ShootStrategy*) new SingleLineShooting();
	m_pImg = this->gameObject->GetComponent<Image>();
	m_pCam = m_pImg->GetCanvas()->GetCamera();
}

void PlayerShip::Update()
{
	int moveX, moveY;
	attribute.vector->y = 0;
	attribute.vector->x = 0;

	m_cdTimer -= Game::deltaTime;

	if (m_KeyboardStates[SDL_SCANCODE_W])
		attribute.vector->y = -1;
	if (m_KeyboardStates[SDL_SCANCODE_S])
		attribute.vector->y = 1;
	if (m_KeyboardStates[SDL_SCANCODE_A])
		attribute.vector->x = -1;
	if (m_KeyboardStates[SDL_SCANCODE_D])
		attribute.vector->x = 1;

	string spriteName = "MainShip.png";

	if (attribute.vector->x <= 0)
	{
		if (attribute.vector->y < 0)
			spriteName = "MainShipUp.png";
		if (attribute.vector->y > 0)
			spriteName = "MainShipDown.png";
	}
	else
	{
		if (attribute.vector->y < 0)
			spriteName = "MainShipUpForward.png";
		if (attribute.vector->y > 0)
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

	GetMovePixel(attribute.vector, attribute.speed, &moveX, &moveY);

	Transform camPos;
	GetCamPosition(m_pCam, *this->transform->position, camPos.position);

	camPos.position->x += moveX + (m_lastCamPosX - camPos.position->x);
	camPos.position->y += moveY;

	m_lastCamPosX = camPos.position->x;

	if (camPos.position->x < 0)
	{
		camPos.position->x = 0;
	}

	if (camPos.position->y + transform->size->y * transform->scale->y > Game::screenH)
	{
		camPos.position->y = Game::screenH - transform->size->y * transform->scale->y;
	}

	if (camPos.position->x < 0)
	{
		camPos.position->x = 0;
	}

	if (camPos.position->x + transform->size->x * transform->scale->x > Game::screenW)
	{
		camPos.position->x = Game::screenW - transform->size->x * transform->scale->x;
	}

	GetRealPosition(m_pCam, *camPos.position, this->transform->position);

	cout << this->transform->position->x << endl;
	if (m_KeyboardStates[SDL_SCANCODE_SPACE])
	{
		if (m_cdTimer <= 0)
		{
			Vector2 pos;
			ReactAttribute rectAttr;
			ItemAttribute attr;
			attr.atk = 1;
			attr.hp = 1;
			attr.speed = 400;
			attr.vector = new Vector2(1, 0);
			rectAttr.camp = Camp::Ally;
			rectAttr.reactValue = -attr.atk;
			rectAttr.target = ReactCamp::EnemyOnly;
			rectAttr.type = ReactType::HP;

			m_shooting->Fire(this->transform, attr, rectAttr);
			m_cdTimer = m_attackCD;
		}
	}
}