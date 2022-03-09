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
};
