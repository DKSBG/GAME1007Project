#pragma once
#include<SDL.h>
#include <iostream>
#include "resource.h"
using namespace std;

struct PlayerInfo
{
	int playTimes;
};

class Game {
public:
	virtual bool Init(const char* title,
		int x, int y, int w,
		int h, Uint32 flags) = NULL;
	virtual void Update() = NULL;
	virtual void Render() = NULL;
	virtual void EventHandler() = NULL;
	virtual void Clean() = NULL;
	virtual bool IsRunning() = NULL;
	virtual void EndOfFrame() = NULL;
	virtual PlayerInfo* GetPlayerInfo() = NULL;
	SDL_Renderer* GetRenderer();
	static Game* GetInstance();
	static long deltaGameTime;
	static long deltaTime;
	static int screenH, screenW;
	void Pause();
	void Resume();
	void Reloading();
	void Reload(std::string scene);
	void Start();
	bool quit;
protected:
	static bool m_running;
	static bool m_isPause;
	static bool m_isReloading;
	static std::string m_sceneName;
	static SDL_Window* m_pWindow;
	static SDL_Renderer* m_pRenderer;
	static Game* s_pInstance;
	long m_lastFrameEndTime;
	long m_accumulateGameTime;

};

class MainGame : public Game {
public:
	bool Init(const char* title,
		int x, int y, int w,
		int h, Uint32 flags);
	void Update();
	void Render();
	void Reflesh();
	void EventHandler();
	void Clean();
	bool IsRunning();
	void EndOfFrame();
	PlayerInfo* GetPlayerInfo();
private:
	PlayerInfo m_playerInfo{ 3 };
	long m_fixedFrameTime = 16;
	long m_fixedTimer = 0;
};