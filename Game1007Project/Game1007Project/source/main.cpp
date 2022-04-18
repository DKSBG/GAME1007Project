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

	//SceneLoader::GetInstance()->Load("Scene1.xml");
	//std::srand(time(0));

	CameraParser::GetInstance()->Parser("MainCam.xml");
	PrefabParser::GetInstance()->Parser("MainShip.xml");

	pGame->Start();
	while(!pGame->quit)
	{
		pGame->EventHandler();
		pGame->Update();
		CollideManager::GetInstanse()->DetectColliding();
		pGame->Render();
		pGame->Reloading();
		pGame->Reflesh();
		pGame->EndOfFrame();
	}

	return 0;
}