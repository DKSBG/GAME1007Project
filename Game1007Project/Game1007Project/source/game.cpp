#include <iostream>
#include "game.h"
#include "canvas.h"
#include "SDL.h"
#include "colliderManager.h"
#include "SDL_mixer.h"

using namespace std;

#pragma region Game Implement
Game* Game::GetInstance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new MainGame();
	}
	return s_pInstance;
}

SDL_Renderer* Game::GetRenderer()
{
	return m_pRenderer;
}

void Game::Pause() 
{
	m_isPause = true;
}

void Game::Resume() 
{
	m_isPause = false;
}

void Game::Start() 
{
	m_isPause = false;
}

int Game::screenH = 0;
int Game::screenW = 0;

long Game::deltaGameTime = 0;
long Game::deltaTime = 0;
bool Game::m_running = false;
bool Game::m_isPause = false;
SDL_Window* Game::m_pWindow = 0;
SDL_Renderer* Game::m_pRenderer = 0;
Game* Game::s_pInstance = nullptr;
#pragma endregion


#pragma region MainGame
bool MainGame::Init(const char* title,
	int x, int y, int w,
	int h, Uint32 flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL init fail";
		return false;
	}

	m_pWindow = SDL_CreateWindow(
		"First SDL program",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w,
		h,
		SDL_WINDOW_OPENGL);

	if (m_pWindow != 0)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	}
	else
	{
		cout << "Create window fail";
		return false;
	}

	if (m_pRenderer == NULL)
	{
		cout << "Create renderer fail";
		return false;
	}

	screenH = h;
	screenW = w;


	//Initialize SDL_mixer 
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "Create SDL mixer fail";
		return false;
	}

	return true;
}
void MainGame::Update() 
{
	GameObjectManager::GetInstance()->UpdateAllGameObject();
}

void MainGame::Render()
{
	SDL_RenderClear(m_pRenderer);
	GameObjectManager::GetInstance()->PreDrawAllGameObject();
	CanvasManager::GetInstance()->Draw();
	SDL_RenderPresent(m_pRenderer);
}

void MainGame::Reflesh() 
{
	CollideManager::GetInstanse()->RefleshCollideList();
	GameObjectManager::GetInstance()->RefleshGameObjectRelationship();
	GameObjectManager::GetInstance()->RefleshGameObjectList();

}

void MainGame::EventHandler() 
{
	//Handle events on queue
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) 
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}

void MainGame::Clean() {}

bool MainGame::IsRunning() {
	return m_running;
}

void MainGame::EndOfFrame() {
	deltaTime = SDL_GetTicks() - m_lastFrameEndTime;
	m_fixedTimer -= deltaTime;
	if (m_fixedTimer > 0)
	{
		SDL_Delay(m_fixedTimer);
	}

	m_fixedTimer = m_fixedFrameTime;
	m_lastFrameEndTime = SDL_GetTicks();
	deltaTime = m_fixedFrameTime;
	deltaGameTime = 0;
	if (!m_isPause)
		deltaGameTime = deltaTime;
	m_accumulateGameTime += deltaGameTime;
}

PlayerInfo* MainGame::GetPlayerInfo() 
{
	return &m_playerInfo;
}
#pragma endregion


