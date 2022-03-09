#pragma once
#include "SDL.h"
#include "gameObject.h"
#include "image.h"

class InputHandler : GOComponent
{
public:
	void Draw();
	void Update();
	bool quit = false;
private:
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	long m_attackCD = 500;
	long m_cdTimer = 0;
};
