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
#include "SDL_mixer.h"

#define WAV_PATH "minigun-burst-demo.wav"
#define MUS_PATH "minigun-burst-demo.wav"

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


	// Our wave file
	Mix_Chunk* wave1 = NULL;
	Mix_Chunk* wave2 = NULL;
	// Our music file
	Mix_Music* music = NULL;

	//Initialize SDL_mixer 
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return -1;

	SceneLoader::GetInstance()->Load("Scene1.xml");
	pGame->Start();

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