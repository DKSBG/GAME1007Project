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
	SDL_Event event;
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	bool KEYS[];  // 322 is the number of SDLK_DOWN events

};
