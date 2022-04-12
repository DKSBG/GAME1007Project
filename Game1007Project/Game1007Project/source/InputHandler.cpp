//#include"InputHandler.h"
//#include "gameVector.h"
//#include "game.h"
//#include "script.h"
//#include "colliderManager.h"
//#include "collider.h"
//
//void InputHandler::OnCollide(GameObject* go) 
//{
//	Image* pImg;
//	GameObject* pGoExplosion = new GameObject();
//	pImg = new Image("Explosion1.png", 4);
//	pGoExplosion->AddComponent<Image>(pImg);
//	pGoExplosion->GetComponent<Image>()->SetNativeSize();
//
//	Transform* explosionTrs = pGoExplosion->transform;
//	explosionTrs->scale = new Vector2(2, 2);
//
//	explosionTrs->localPosition->x = this->transform->localPosition->x;
//	explosionTrs->localPosition->y = this->transform->localPosition->y;
//	explosionTrs->localPosition->x += this->transform->size->x * this->transform->scale->x / 2;
//	explosionTrs->localPosition->x -= explosionTrs->size->x * explosionTrs->scale->x / 2;
//	explosionTrs->localPosition->y += this->transform->size->y * this->transform->scale->y / 2;
//	explosionTrs->localPosition->y -= explosionTrs->size->y * explosionTrs->scale->y / 2;
//	
//	GameObjectManager::GetInstance()->PopGameObject(this->gameObject);
//}
//
//// This metherd is called by engine each frame.
//void InputHandler::Update()
//{
//	m_cdTimer -= Game::GetInstance()->deltaGameTime;
//
//	if (m_KeyboardStates[SDL_SCANCODE_W])
//	{
//		Vector2* up = transform->localPosition;
//		if (up->y > 0)
//		{
//			up->y -= 5;
//			transform->localPosition = up;
//		}
//	}
//	if (m_KeyboardStates[SDL_SCANCODE_S])
//	{
//		Vector2* down = transform->localPosition;
//		if (down->y < 405)
//		{
//			down->y += 5;
//			transform->localPosition = down;
//		}
//	}
//	if (m_KeyboardStates[SDL_SCANCODE_A])
//	{
//		Vector2* left = transform->localPosition;
//		if (left->x > 0)
//		{
//			left->x -= 5;
//			transform->localPosition = left;
//		}
//	}
//	if (m_KeyboardStates[SDL_SCANCODE_D])
//	{
//		Vector2* right = transform->localPosition;
//		if (right->x < 710)
//		{
//			right->x += 5;
//			transform->localPosition = right;
//		}
//	}
//	if (m_KeyboardStates[SDL_SCANCODE_SPACE])
//	{
//		if (m_cdTimer <= 0)
//		{
//			Image* pImg;
//			GameObject* pGoMainShipBullet = new GameObject();
//			pImg = new Image("MainShipBullet.png", 4);
//			pGoMainShipBullet->AddComponent<Image>(pImg);
//			pGoMainShipBullet->GetComponent<Image>()->SetNativeSize();
//			Transform* bulletTransform = pGoMainShipBullet->transform;
//			bulletTransform->scale = new Vector2(2, 2);
//			bulletTransform->localPosition->x = this->transform->localPosition->x;
//			bulletTransform->localPosition->y = this->transform->localPosition->y;
//			bulletTransform->localPosition->x += this->transform->size->x * this->transform->scale->x;
//			bulletTransform->localPosition->y += bulletTransform->size->x * bulletTransform->scale->x;
//			bulletTransform->localPosition->y -= (bulletTransform->size->y * bulletTransform->scale->y) / 2;
//
//			PlayerShipProjectile* bullet = new PlayerShipProjectile();
//			bullet->moveVector.x = 1;
//			bullet->moveVector.y = 0;
//			bullet->speed = 200;
//
//			pGoMainShipBullet->AddComponent<Collider>(new Collider());
//			pGoMainShipBullet->AddComponent<Ally>(bullet);
//			m_cdTimer = m_attackCD;
//
//			m_cdTimer = m_attackCD;
//		}
//	}
//	else
//	{
//		false;
//	}
//}
