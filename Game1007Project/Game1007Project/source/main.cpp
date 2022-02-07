#include "SDL.h"
#include "SDL_image.h"
#include "game.h"
#include "gameObject.h"
#include "image.h"
#include "animation.h"

// Marcos Comment to try if it work
int main(int argc, char* argv[])
{
	MainGame *pGame = new MainGame();
	pGame->Init(
		"First SDL program",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL);

	GameObject* go = new GameObject();
	Image* imgExample = new Image("Flight1.png",100);
	go->AddComponent<Image>(imgExample);

	GameObject* go2 = new GameObject();
	AtlasResource* atlas = ResourceManager::GetInstance()->LoadAtlasResource("flybat.png");
	atlas->AutoSplite(4, 4);
	Animation* animExample = new Animation("flybat.png", 200, 0, 3, 160);
	go2->AddComponent<Animation>(animExample);
	animExample->transform->scale->x = 3.5;
	animExample->transform->scale->y = 3.5;
	animExample->transform->position->x = 320;
	animExample->transform->position->y = 240;

	while(1)
	{
		pGame->deltaTime = 16;
		go->transform->position->x += 2;
		go->transform->position->y += 2;
		pGame->Update();
		pGame->Render();
		SDL_Delay(16);
	}

	return 0;
}

