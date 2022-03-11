#pragma once
#include "SDL.h"
#include "gameObject.h"
#include "image.h"

class InputHandler : GOComponent
{
public:
	void Update();
	void OnCollide(GameObject *go);
	bool quit = false;
private:
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	long m_attackCD = 200;
	long m_cdTimer = 0;
};
