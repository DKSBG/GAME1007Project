#include"InputHandler.h"
#include "gameVector.h"
#include "game.h"
#include "script.h"
#include "colliderManager.h"

void InputHandler::OnCollide(GameObject* go) 
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

// This metherd is called by engine each frame.
void InputHandler::Update()
{
	m_cdTimer -= Game::GetInstance()->deltaTime;

	if (m_KeyboardStates[SDL_SCANCODE_W])
	{
		Vector2* up = transform->position;
		if (up->y > 0)
		{
			up->y -= 5;
			transform->position = up;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_S])
	{
		Vector2* down = transform->position;
		if (down->y < 405)
		{
			down->y += 5;
			transform->position = down;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_A])
	{
		Vector2* left = transform->position;
		if (left->x > 0)
		{
			left->x -= 5;
			transform->position = left;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_D])
	{
		Vector2* right = transform->position;
		if (right->x < 710)
		{
			right->x += 5;
			transform->position = right;
		}
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
			bulletTransform->position->y += bulletTransform->size->x * bulletTransform->scale->x;
			bulletTransform->position->y -= (bulletTransform->size->y * bulletTransform->scale->y) / 2;

			ExampleProjectileScript* pProjectileScrip = new ExampleProjectileScript();
			Vector2 flyVector;
			flyVector.x = 10;
			flyVector.y = 0;
			pProjectileScrip->SetFlyVector(flyVector);
			pGoMainShipBullet->AddComponent<ExampleProjectileScript>(pProjectileScrip);

			m_cdTimer = m_attackCD;
		}
	}
	else
	{
		false;
	}
}
