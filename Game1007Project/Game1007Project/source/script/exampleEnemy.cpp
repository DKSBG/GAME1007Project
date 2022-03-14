#include "gameObject.h"
#include "image.h"
#include "script.h"
#include "collider.h"
#include "math.h"
#include "tools.h"

void ExampleEnemyShip::Init()
{
	speed = 100;
	moveVector.x = 0;
	moveVector.y = -1;
	m_attackCD = 750;
}

void ExampleEnemyShip::UnderAttack() 
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

void ExampleEnemyShip::Update()
{
	m_cdTimer -= Game::deltaTime;
	int moveX, moveY;
	GetMovePixel(&moveVector, speed, &moveX, &moveY);
	transform->position->x += moveX;

	if (transform->position->y + moveY <= 0 || 
		transform->position->y + moveY + (transform->size->y * transform->scale->y) >= Game::screenH)
	{
		moveY = -moveY;
		moveVector.y = -moveVector.y;
	}
	transform->position->y += moveY;

	if (m_cdTimer < 0) 
	{
		Image* pImg;
		GameObject* bullet = new GameObject();
		pImg = new Image("Enemy1bullet.png", 4);
		bullet->AddComponent<Image>(pImg);
		bullet->GetComponent<Image>()->SetNativeSize();
		Transform* bulletTransform = bullet->transform;
		bulletTransform->scale = new Vector2(1, 1);
		bulletTransform->position->x = this->transform->position->x;
		bulletTransform->position->y = this->transform->position->y;
		bulletTransform->position->x -= bulletTransform->size->x * bulletTransform->scale->x;
		bulletTransform->position->y += this->transform->size->y * this->transform->scale->y / 2;
		bulletTransform->position->y -= bulletTransform->size->y * bulletTransform->scale->y / 2;

		ExampleEnemyProjectle* bulletScript = new ExampleEnemyProjectle();
		bulletScript->speed = 200;
		bulletScript->moveVector.x = -1;
		bulletScript->moveVector.y = 0;
		bullet->AddComponent<Enemy>(bulletScript);
		m_cdTimer = m_attackCD;
		bullet->AddComponent<Collider>(new Collider());
	}
}

void ExampleEnemyProjectle::Init() {}
void ExampleEnemyProjectle::UnderAttack() {}
void ExampleEnemyProjectle::Update() 
{
	int moveX, moveY;
	GetMovePixel(&moveVector, speed, &moveX, &moveY);
	transform->position->x += moveX;
	transform->position->y += moveY;
}
