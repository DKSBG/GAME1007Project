#pragma once
#include "SDL.h"
#include "gameObject.h"
#include "game.h"

class InputHandler : GOComponent
{
public:
	void Draw();
	void Update();
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(0);
	SDL_Event event;
};
