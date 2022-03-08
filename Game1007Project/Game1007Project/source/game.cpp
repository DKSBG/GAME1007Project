#include <iostream>
#include "game.h"
#include "canvas.h"

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

int Game::deltaTime = 0;
bool Game::m_running = false;
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
	GameObjectManager::GetInstance()->RefleshGameObjectList();
}

void MainGame::HandlerEvent() {}
void MainGame::Clean() {}

bool MainGame::IsRunning() {
	return m_running;
}
#pragma endregion


