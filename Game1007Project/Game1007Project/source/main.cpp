#include "SDL.h"
#include "SDL_image.h"
#include "game.h"
#include "gameObject.h"
#include "image.h"
#include "animation.h"
#include "InputHandler.h"
#include "colliderManager.h"
#include "collider.h"
//For example.

// Marcos Comment to try if it work
int main(int argc, char* argv[])
{
	MainGame *pGame = new MainGame();
	pGame->Init(
		"First SDL program",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		768,
		432,
		SDL_WINDOW_OPENGL);

	Image* pImg;

	GameObject* pGoBackground = new GameObject();
	pImg = new Image("Background.png", 0);
	pGoBackground->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoBackground->transform->scale = new Vector2(2,2);

	GameObject* pGoMoon = new GameObject();
	pImg = new Image("Moon.png", 1);
	pGoMoon->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoMoon->transform->scale = new Vector2(2, 2);

	GameObject* pGoBackgroundCloud = new GameObject();
	pImg = new Image("BackgroundCloud.png", 1);
	pGoBackgroundCloud->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoBackgroundCloud->transform->scale = new Vector2(2, 2);

	GameObject* pGoMountain = new GameObject();
	pImg = new Image("Mountain.png", 2);
	pGoMountain->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoMountain->transform->scale = new Vector2(2, 2);

	GameObject* pGoCloud = new GameObject();
	pImg = new Image("Cloud.png", 5);
	pGoCloud->AddComponent<Image>(pImg);
	pGoCloud->GetComponent<Image>()->SetNativeSize();
	pGoCloud->transform->scale = new Vector2(2, 2);

	GameObject* pGoStartGrond = new GameObject();
	pImg = new Image("StartGround.png", 3);
	pGoStartGrond->AddComponent<Image>(pImg);
	pGoStartGrond->GetComponent<Image>()->SetNativeSize();
	pGoStartGrond->transform->scale = new Vector2(2, 2);
	pGoStartGrond->transform->position = new Vector2(516, 278);

	GameObject* pGoEndGrond = new GameObject();
	pImg = new Image("EndGround.png", 3);
	pGoEndGrond->AddComponent<Image>(pImg);
	pGoEndGrond->GetComponent<Image>()->SetNativeSize();
	pGoEndGrond->transform->scale = new Vector2(2, 2);
	pGoEndGrond->transform->position = new Vector2(0, 284);

	GameObject* pGoMainShip = new GameObject();
	pImg = new Image("MainShip.png", 4);
	pGoMainShip->AddComponent<Image>(pImg);
	pGoMainShip->GetComponent<Image>()->SetNativeSize();
	pGoMainShip->transform->scale = new Vector2(2,2);
	pGoMainShip->transform->position = new Vector2(0, 0);

	GameObject* pGoTurret = new GameObject();
	pImg = new Image("Turret.png", 4);
	pGoTurret->AddComponent<Image>(pImg);
	pGoTurret->GetComponent<Image>()->SetNativeSize();
	pGoTurret->transform->scale = new Vector2(2, 2);
	pGoTurret->transform->position = new Vector2(545, 260);

	GameObject* pGoTurretBullet = new GameObject();
	pImg = new Image("TurretBullet.png", 4);
	pGoTurretBullet->AddComponent<Image>(pImg);
	pGoTurretBullet->GetComponent<Image>()->SetNativeSize();
	pGoTurretBullet->transform->scale = new Vector2(2, 2);
	pGoTurretBullet->transform->position = new Vector2(480, 220);
	
	GameObject* pGoExplosion1 = new GameObject();
	pImg = new Image("Explosion1.png", 4);
	pGoExplosion1->AddComponent<Image>(pImg);
	pGoExplosion1->GetComponent<Image>()->SetNativeSize();
	pGoExplosion1->transform->scale = new Vector2(2, 2);
	pGoExplosion1->transform->position = new Vector2(320, 150);

	GameObject* pGoEnemy1 = new GameObject();
	pImg = new Image("Enemy1.png", 4);
	pGoEnemy1->AddComponent<Image>(pImg);
	pGoEnemy1->GetComponent<Image>()->SetNativeSize();
	pGoEnemy1->transform->scale = new Vector2(1.5, 1.5);
	pGoEnemy1->transform->position = new Vector2(700, 190);
	
	GameObject* pGoEnemy1Bullet = new GameObject();
	pImg = new Image("Enemy1bullet.png", 4);
	pGoEnemy1Bullet->AddComponent<Image>(pImg);
	pGoEnemy1Bullet->GetComponent<Image>()->SetNativeSize();
	pGoEnemy1Bullet->transform->scale = new Vector2(1.5, 1.5);
	pGoEnemy1Bullet->transform->position = new Vector2(610, 205);

	pGoMainShip->AddComponent<InputHandler>(new InputHandler());
	Collider *collider = pGoMainShip->AddComponent<Collider>(new Collider());
	collider->colliderInfo->detectRange = new Vector2(0.8, 0.5);
	pGoEnemy1->AddComponent<Collider>(new Collider());
	pGoTurret->AddComponent<Collider>(new Collider());
	pGoEnemy1Bullet->AddComponent<Collider>(new Collider());
	pGoTurretBullet->AddComponent<Collider>(new Collider());
	pGoStartGrond->AddComponent<Collider>(new Collider());
	pGoEndGrond->AddComponent<Collider>(new Collider());

	while(1)
	{
		CollideManager::GetInstanse()->DetectColliding();
		pGame->EventHandler();
		pGame->Update();
		pGame->Render();
		pGame->Reflesh();
		pGame->EndOfFrame();
		SDL_Delay(16);
	}

	return 0;
}