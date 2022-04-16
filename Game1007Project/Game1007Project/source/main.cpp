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
#include "gameController.h"
#include "camera.h"
#include "infinityScrollMap.h"
#include "dataParser.h"


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

	SceneLoader::GetInstance()->Load("Scene1.xml");

	//Camera* cam = CameraParser::GetInstance()->Parser("mainCam.xml");
	//GameObject* go = PrefabParser::GetInstance()->Parser("mainShip.xml");
	//GameObject* go1 = PrefabParser::GetInstance()->Parser("snowground.xml");

	//delete go;
	//GameObject* m_pPlayerTimesArea = PrefabParser::GetInstance()->Parser("playTimesArea.xml");
	//m_pPlayerTimesArea->transform.localPosition.Set(10, 10);
	//std::vector<GameObject*> m_pPlayerTimeIcons;
	//std::vector<GameObject*> pChildren = m_pPlayerTimesArea->GetChildren();
	//for (int index = 0; index < pChildren.size(); index++)
	//{
	//	m_pPlayerTimeIcons.push_back(pChildren[index]);
	//}
	//m_pPlayerTimeIcons[0]->isActive = true;
	//m_pPlayerTimeIcons[1]->isActive = false;
	//m_pPlayerTimeIcons[2]->isActive = true;
	//go1->SetParent(go);
	//go1->transform.localPosition.Set(60, 60);

	//go->isActive = false;

	//int count = 0;
	pGame->Start();
	while(!pGame->quit)
	{
		pGame->EventHandler();
		pGame->Update();
		CollideManager::GetInstanse()->DetectColliding();
		pGame->Render();
		pGame->Reflesh();
		pGame->EndOfFrame();
	}

	return 0;
}