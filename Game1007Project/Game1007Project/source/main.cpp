#include "SDL.h"
#include "SDL_image.h"
#include "game.h"
#include "gameObject.h"
#include "image.h"
#include "animation.h"
#include "InputHandler.h"
#include "colliderManager.h"
#include "collider.h"
#include "reactableItem.h"
#include "camera.h"
#include "infinityScrollMap.h"
//#include "script.h"
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

	Transform trs;
	trs.position.Set(0, 0);
	trs.size.Set(MainGame::screenW, MainGame::screenH);
	trs.scale.Set(1, 1);
	CameraManager::GetInstance()->CreateCamera("MainCam", trs);
	CameraManager::GetInstance()->CreateCamera("BackgroundCam", trs);
	CameraManager::GetInstance()->CreateCamera("CloudCam", trs);
	CameraManager::GetInstance()->CreateCamera("MountCam", trs);


	Camera* pMainCam = CameraManager::GetInstance()->GetCamera("MainCam");
	Camera* pBackgroudCam = CameraManager::GetInstance()->GetCamera("BackgroundCam");
	Camera* pCloudCam = CameraManager::GetInstance()->GetCamera("CloudCam");
	Camera* pMountainCam = CameraManager::GetInstance()->GetCamera("MountCam");

	CanvasManager::GetInstance()->TryGetCanvas(0)->SetCamera(pBackgroudCam);
	CanvasManager::GetInstance()->TryGetCanvas(1)->SetCamera(pCloudCam);
	CanvasManager::GetInstance()->TryGetCanvas(2)->SetCamera(pMountainCam);
	CanvasManager::GetInstance()->TryGetCanvas(3)->SetCamera(pMainCam);
	CanvasManager::GetInstance()->TryGetCanvas(4)->SetCamera(pMainCam);
	CanvasManager::GetInstance()->TryGetCanvas(5)->SetCamera(pMainCam);

	Image* pImg;
	InfinityScrollMap* pInfinityScrollMap;

	GameObject* pGoBackground = new GameObject();
	pImg = new Image("Background.png", 0);
	pGoBackground->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoBackground->transform.scale.Set(2,2);

	GameObject* pGoMoon = new GameObject();
	pImg = new Image("Moon.png", 0);
	pGoMoon->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoMoon->transform.scale.Set(2, 2);

	GameObject* pGoBackgroundCloudL = new GameObject();
	pImg = new Image("BackgroundCloud.png", 1);
	pGoBackgroundCloudL->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoBackgroundCloudL->transform.scale.Set(2, 2);

	GameObject* pGoBackgroundCloudR = new GameObject();
	pImg = new Image("BackgroundCloud.png", 1);
	pGoBackgroundCloudR->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pGoBackgroundCloudR->transform.scale.Set(2, 2);;
	pGoBackgroundCloudR->transform.position.Set(pGoBackgroundCloudR->transform.size.x * 2, 0);

	GameObject* pScrollCloud = new GameObject();
	pInfinityScrollMap = new InfinityScrollMap();
	pInfinityScrollMap->mapCam = &pCloudCam->trs;
	pInfinityScrollMap->mapL = &pGoBackgroundCloudL->transform;
	pInfinityScrollMap->mapR = &pGoBackgroundCloudR->transform;
	pInfinityScrollMap->moveSpeed = 20;
	pScrollCloud->AddComponent<InfinityScrollMap>(pInfinityScrollMap);


	GameObject* pBackgroundMountainL = new GameObject();
	pImg = new Image("Mountain.png", 2);
	pBackgroundMountainL->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pBackgroundMountainL->transform.scale.Set(2, 2);


	GameObject* pBackgroundMountainR = new GameObject();
	pImg = new Image("Mountain.png", 2);
	pBackgroundMountainR->AddComponent<Image>(pImg);
	pImg->SetNativeSize();
	pBackgroundMountainR->transform.scale.Set(2, 2);
	pBackgroundMountainR->transform.position.Set(pBackgroundMountainR->transform.size.x * 2, 0);

	GameObject* pScollMountain= new GameObject();
	pInfinityScrollMap = new InfinityScrollMap();
	pInfinityScrollMap->mapCam = &pMountainCam->trs;
	pInfinityScrollMap->mapL = &pBackgroundMountainL->transform;
	pInfinityScrollMap->mapR = &pBackgroundMountainR->transform;
	pInfinityScrollMap->moveSpeed = 50;
	pScollMountain->AddComponent<InfinityScrollMap>(pInfinityScrollMap);


	GameObject* pGoCloud = new GameObject();
	pImg = new Image("Cloud.png", 5);
	pGoCloud->AddComponent<Image>(pImg);
	pGoCloud->GetComponent<Image>()->SetNativeSize();
	pGoCloud->transform.scale.Set(2, 2);

	GameObject* pGoStartGrond = new GameObject();
	pImg = new Image("StartGround.png", 3);
	pGoStartGrond->AddComponent<Image>(pImg);
	pGoStartGrond->GetComponent<Image>()->SetNativeSize();
	pGoStartGrond->transform.scale.Set(2, 2);
	pGoStartGrond->transform.position.Set(516, 278);

	GameObject* pGoEndGrond = new GameObject();
	pImg = new Image("EndGround.png", 3);
	pGoEndGrond->AddComponent<Image>(pImg);
	pGoEndGrond->GetComponent<Image>()->SetNativeSize();
	pGoEndGrond->transform.scale.Set(2, 2);
	pGoEndGrond->transform.position.Set(0, 284);

	GameObject* pGoMainShip = new GameObject();
	pImg = new Image("MainShip.png", 4);
	pGoMainShip->AddComponent<Image>(pImg);
	pGoMainShip->GetComponent<Image>()->SetNativeSize();
	pGoMainShip->transform.scale.Set(2,2);
	pGoMainShip->transform.position.Set(0, 0);

	GameObject* pGoTurret = new GameObject();
	pImg = new Image("Turret.png", 4);
	pGoTurret->AddComponent<Image>(pImg);
	pGoTurret->GetComponent<Image>()->SetNativeSize();
	pGoTurret->transform.scale.Set(2, 2);
	pGoTurret->transform.position.Set(545, 260);

	//GameObject* pGoTurretBullet = new GameObject();
	//pImg = new Image("TurretBullet.png", 4);
	//pGoTurretBullet->AddComponent<Image>(pImg);
	//pGoTurretBullet->GetComponent<Image>()->SetNativeSize();
	//pGoTurretBullet->transform->scale = new Vector2(2, 2);
	//pGoTurretBullet->transform->position = new Vector2(480, 220);
	
	//GameObject* pGoExplosion1 = new GameObject();
	//pImg = new Image("Explosion1.png", 4);
	//pGoExplosion1->AddComponent<Image>(pImg);
	//pGoExplosion1->GetComponent<Image>()->SetNativeSize();
	//pGoExplosion1->transform->scale = new Vector2(2, 2);
	//pGoExplosion1->transform->position = new Vector2(320, 150);

	GameObject* pGoEnemy1 = new GameObject();
	pImg = new Image("Enemy1.png", 4);
	pGoEnemy1->AddComponent<Image>(pImg);
	pGoEnemy1->GetComponent<Image>()->SetNativeSize();
	pGoEnemy1->transform.scale.Set(1.5, 1.5);
	pGoEnemy1->transform.position.Set(700, 190);
	
	//GameObject* pGoEnemy1Bullet = new GameObject();
	//pImg = new Image("Enemy1bullet.png", 4);
	//pGoEnemy1Bullet->AddComponent<Image>(pImg);
	//pGoEnemy1Bullet->GetComponent<Image>()->SetNativeSize();
	//pGoEnemy1Bullet->transform->scale = new Vector2(1.5, 1.5);
	//pGoEnemy1Bullet->transform->position = new Vector2(610, 205);

	ReactableItem* mainShip = new PlayerShip(); 
	pGoMainShip->AddComponent<ReactableItem>(mainShip);
	mainShip->Init();
	pGoMainShip->AddComponent<Collider>(new Collider());

	ReactableItem* enemy1Ship = new Enemy1Ship();
	pGoEnemy1->AddComponent<ReactableItem>(enemy1Ship);
	enemy1Ship->Init();
	pGoEnemy1->AddComponent<Collider>(new Collider());

	ReactableItem* startGroundObstacle = new Obstacle();
	pGoStartGrond->AddComponent<ReactableItem>(startGroundObstacle);
	startGroundObstacle->Init();
	pGoStartGrond->AddComponent<Collider>(new Collider());

	ReactableItem* endGroundObstacle = new Obstacle();
	pGoEndGrond->AddComponent<ReactableItem>(endGroundObstacle);
	endGroundObstacle->Init();
	pGoEndGrond->AddComponent<Collider>(new Collider());
	
	//Collider *collider = pGoMainShip->AddComponent<Collider>(new Collider());
	//collider->colliderInfo->detectRange = new Vector2(0.8, 0.5);
	//pGoEnemy1->AddComponent<Collider>(new Collider());
	//pGoTurret->AddComponent<Collider>(new Collider());
	//pGoEnemy1Bullet->AddComponent<Collider>(new Collider());
	//pGoTurretBullet->AddComponent<Collider>(new Collider());
	//pGoStartGrond->AddComponent<Collider>(new Collider());
	//pGoEndGrond->AddComponent<Collider>(new Collider());

	int index = 20;

	while(1)
	{
		pMainCam->trs.position.x += (float)100 / 1000 * MainGame::deltaTime;;
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