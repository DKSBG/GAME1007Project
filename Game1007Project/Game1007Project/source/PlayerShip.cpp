#include "script.h"
#include "gameObject.h"
#include "gameVector.h"
#include "game.h"
#include "image.h"
#include "colliderManager.h"
#include "collider.h"
#include "tools.h"

void PlayerShip::Init() 
{
	speed = 400;
}

void PlayerShip::UnderAttack() 
{
	Image* pImg;
	GameObject* pGoExplosion = new GameObject();
	pImg = new Image("Explosion1.png", 4);
	pGoExplosion->AddComponent<Image>(pImg);
	pGoExplosion->GetComponent<Image>()->SetNativeSize();

	Transform* explosionTrs = pGoExplosion->transform;
	explosionTrs->scale = new Vector2(2, 2);

	explosionTrs->position->x = this->transform->position->x;
	explosionTrs->position->y = this->transform->position->y;
	explosionTrs->position->x += this->transform->size->x * this->transform->scale->x / 2;
	explosionTrs->position->x -= explosionTrs->size->x * explosionTrs->scale->x / 2;
	explosionTrs->position->y += this->transform->size->y * this->transform->scale->y / 2;
	explosionTrs->position->y -= explosionTrs->size->y * explosionTrs->scale->y / 2;

	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
}

void PlayerShip::Update() 
{
	m_cdTimer -= Game::GetInstance()->deltaTime;

	int moveX, moveY;
	moveVector.y = 0;
	moveVector.x = 0;

	if (m_KeyboardStates[SDL_SCANCODE_W])
		moveVector.y = -1;
	if (m_KeyboardStates[SDL_SCANCODE_S])
		moveVector.y = 1;
	if (m_KeyboardStates[SDL_SCANCODE_A])
		moveVector.x = -1;
	if (m_KeyboardStates[SDL_SCANCODE_D])
		moveVector.x = 1;

	GetMovePixel(&moveVector, speed, &moveX, &moveY);

	this->transform->position->y += moveY;
	this->transform->position->x += moveX;

	if (this->transform->position->y < 0)
	{
		this->transform->position->y = 0;
	}

	if (this->transform->position->y + transform->size->y * transform->scale->y > Game::screenH)
	{
		this->transform->position->y = Game::screenH - transform->size->y * transform->scale->y;
	}

	if (transform->position->x < 0)
	{
		transform->position->x = 0;
	}

	if (transform->position->x + transform->size->x * transform->scale->x > Game::screenW)
	{
		transform->position->x = Game::screenW - transform->size->x * transform->scale->x;
	}

	if (m_KeyboardStates[SDL_SCANCODE_SPACE])
	{
		if (m_cdTimer <= 0)
		{
			Image* pImg;
			GameObject* pGoMainShipBullet = new GameObject();
			pImg = new Image("MainShipBullet.png", 4);
			pGoMainShipBullet->AddComponent<Image>(pImg);
			pGoMainShipBullet->GetComponent<Image>()->SetNativeSize();
			Transform* bulletTransform = pGoMainShipBullet->transform;
			bulletTransform->scale = new Vector2(2, 2);
			bulletTransform->position->x = this->transform->position->x;
			bulletTransform->position->y = this->transform->position->y;
			bulletTransform->position->x += this->transform->size->x * this->transform->scale->x;
			bulletTransform->position->y += this->transform->size->y * this->transform->scale->y / 2;
			bulletTransform->position->y -= bulletTransform->size->y * bulletTransform->scale->y / 2;

			PlayerShipProjectile* bullet = new PlayerShipProjectile();
			bullet->moveVector.x = 1;
			bullet->moveVector.y = 0;
			bullet->speed = 400;

			pGoMainShipBullet->AddComponent<Collider>(new Collider());
			pGoMainShipBullet->AddComponent<Ally>(bullet);
			m_cdTimer = m_attackCD;
		}
	}
	else
	{
		false;
	}
}

void PlayerShipProjectile::Init() {}
void PlayerShipProjectile::UnderAttack() {}
void PlayerShipProjectile::Update()
{
	int moveX, moveY;
	GetMovePixel(&moveVector, speed, &moveX, &moveY);
	transform->position->x += moveX;
	transform->position->y += moveY;
}