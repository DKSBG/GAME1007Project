#pragma once
#include<SDL.h>
#include <iostream>
#include "resource.h"
using namespace std;

class Game {
public:
	virtual bool Init(const char* title,
		int x, int y, int w,
		int h, Uint32 flags) = NULL;
	virtual void Update() = NULL;
	virtual void Render() = NULL;
	virtual void HandlerEvent() = NULL;
	virtual void Clean() = NULL;
	virtual bool IsRunning() = NULL;
	SDL_Renderer* GetRenderer();
	static Game* GetInstance();
	static int deltaTime;
protected:
	static bool m_running;
	static SDL_Window* m_pWindow;
	static SDL_Renderer* m_pRenderer;
	static Game* s_pInstance;
};

class MainGame : public Game {
public:
	bool Init(const char* title,
		int x, int y, int w,
		int h, Uint32 flags);
	void Update();
	void Render();
	void HandlerEvent();
	void Clean();
	bool IsRunning();
};