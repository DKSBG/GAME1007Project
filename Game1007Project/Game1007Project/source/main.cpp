#include "SDL.h"
#include "SDL_image.h"
#include "game.h"
#include "gameObject.h"
#include "image.h"
#include "animation.h"
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

	/*GameObject* go = new GameObject();
	Image* imgExample = new Image("Flight1.png",100);
	go->AddComponent<Image>(imgExample);

	GameObject* go2 = new GameObject();
	AtlasResource* atlas = ResourceManager::GetInstance()->LoadAtlasResource("flybat.png");
	atlas->AutoSplite(4, 4);
	Animation* animExample = new Animation("flybat.png", 200, 1, 3, 160);
	go2->AddComponent<Animation>(animExample);
	animExample->transform->scale->x = 1;
	animExample->transform->scale->y = 1;
	animExample->transform->position->x = 320;
	animExample->transform->position->y = 240;*/
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
	pImg = new Image("Cloud.png", 2);
	pGoCloud->AddComponent<Image>(pImg);
	pGoCloud->GetComponent<Image>()->SetNativeSize();
	pGoCloud->transform->scale = new Vector2(2, 2);
	

	while(1)
	{
		/*pGame->deltaTime = 16;
		go->transform->position->x += 2;
		go->transform->position->y += 2;*/
		pGame->Update();
		pGame->Render();
		SDL_Delay(16);
	}

	return 0;
}