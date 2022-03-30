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
#include "dataParser.h"

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
	CameraManager::GetInstance()->CreateCamera("ForeGroundCloudCam", trs);

	Camera* pMainCam = CameraManager::GetInstance()->GetCamera("MainCam");
	Camera* pBackgroudCam = CameraManager::GetInstance()->GetCamera("BackgroundCam");
	Camera* pCloudCam = CameraManager::GetInstance()->GetCamera("CloudCam");
	Camera* pMountainCam = CameraManager::GetInstance()->GetCamera("MountCam");
	Camera* pFOrGroundCloudCam = CameraManager::GetInstance()->GetCamera("ForeGroundCloudCam");

	CanvasManager::GetInstance()->TryGetCanvas(0)->SetCamera(pBackgroudCam);
	CanvasManager::GetInstance()->TryGetCanvas(1)->SetCamera(pCloudCam);
	CanvasManager::GetInstance()->TryGetCanvas(2)->SetCamera(pMountainCam);
	CanvasManager::GetInstance()->TryGetCanvas(3)->SetCamera(pMainCam);
	CanvasManager::GetInstance()->TryGetCanvas(4)->SetCamera(pMainCam);
	CanvasManager::GetInstance()->TryGetCanvas(5)->SetCamera(pFOrGroundCloudCam);

	Image* pImg;
	InfinityScrollMap* pInfinityScrollMap;

	GameObject* pGoBackground = PrefabParser::GetInstance()->Parser("background.xml");
	GameObject* pGoMoon = PrefabParser::GetInstance()->Parser("moon.xml");

	GameObject* pGoBackgroundCloudL = PrefabParser::GetInstance()->Parser("backgroundCloud.xml");
	GameObject* pGoBackgroundCloudR = PrefabParser::GetInstance()->Parser("backgroundCloud.xml");
	pGoBackgroundCloudR->transform.position.Set(pGoBackgroundCloudR->transform.size.x * 2, 0);

	GameObject* pScrollCloud = new GameObject();
	pInfinityScrollMap = new InfinityScrollMap();
	pInfinityScrollMap->mapCam = &pCloudCam->trs;
	pInfinityScrollMap->mapL = &pGoBackgroundCloudL->transform;
	pInfinityScrollMap->mapR = &pGoBackgroundCloudR->transform;
	pInfinityScrollMap->moveSpeed = 20;
	pScrollCloud->AddComponent<InfinityScrollMap>(pInfinityScrollMap);

	GameObject* pBackgroundMountainL = PrefabParser::GetInstance()->Parser("backgroundMountain.xml");
	GameObject* pBackgroundMountainR = PrefabParser::GetInstance()->Parser("backgroundMountain.xml");
	pBackgroundMountainR->transform.position.Set(pBackgroundMountainR->transform.size.x * 2, 0);

	GameObject* pScollMountain= new GameObject();
	pInfinityScrollMap = new InfinityScrollMap();
	pInfinityScrollMap->mapCam = &pMountainCam->trs;
	pInfinityScrollMap->mapL = &pBackgroundMountainL->transform;
	pInfinityScrollMap->mapR = &pBackgroundMountainR->transform;
	pInfinityScrollMap->moveSpeed = 50;
	pScollMountain->AddComponent<InfinityScrollMap>(pInfinityScrollMap);

	GameObject* pGoCloudL = PrefabParser::GetInstance()->Parser("foregroundCloud.xml");
	GameObject* pGoCloudR = PrefabParser::GetInstance()->Parser("foregroundCloud.xml");
	pGoCloudR->transform.position.Set(pBackgroundMountainR->transform.size.x * 2, 0);

	GameObject* pScollForeGroundCloud = new GameObject();
	pInfinityScrollMap = new InfinityScrollMap();
	pInfinityScrollMap->mapCam = &pFOrGroundCloudCam->trs;
	pInfinityScrollMap->mapL = &pGoCloudL->transform;
	pInfinityScrollMap->mapR = &pGoCloudR->transform;
	pInfinityScrollMap->moveSpeed = 150;
	pScollForeGroundCloud->AddComponent<InfinityScrollMap>(pInfinityScrollMap);


	GameObject* pSnowGrond = PrefabParser::GetInstance()->Parser("snowGround.xml");
	pSnowGrond->transform.position.Set(516, 278);

	GameObject* pGoMainShip = PrefabParser::GetInstance()->Parser("mainShip.xml");
	pGoMainShip->transform.position.Set(0, 0);

	GameObject* pGoTurret = PrefabParser::GetInstance()->Parser("turret.xml");
	pGoTurret->transform.position.Set(545, 260);

	GameObject* pGoEnemy1 = PrefabParser::GetInstance()->Parser("enemy1.xml");
	pGoEnemy1->transform.position.Set(700, 190);
	
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