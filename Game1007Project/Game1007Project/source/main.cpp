#include "game.h"
#include<SDL.h>
#include<SDL_image.h>

#include "gameObject.h"
#include "image.h"

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
	Image* img = new Image("Flight1.png",100);
	go->AddComponent<Image>(img);
	pGame->Render();

	while(1)
	{
		go->transform->position->x += 2;
		go->transform->position->y += 2;
		pGame->Render();
		SDL_Delay(16);
	}

	return 0;
}

