#include"InputHandler.h"
#include "gameVector.h"


// Script component no need to draw.
void InputHandler::Draw()
{

}


// This metherd is called by engine each frame.
void InputHandler::Update()
{
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
		{
		//User requests quit
		if(event.type == SDL_QUIT)
		{
			quit = true;
		}
	}
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	if (m_KeyboardStates[SDL_SCANCODE_W])
	{
		Vector2* up = transform->position;
		if (up->y > 0)
		{
			up->y -= 4;
			transform->position = up;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_S])
	{
		Vector2* down = transform->position;
		if (down->y < 405)
		{
			down->y += 4;
			transform->position = down;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_A])
	{
		Vector2* left = transform->position;
		if (left->x > 0)
		{
			left->x -= 4;
			transform->position = left;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_D])
	{
		Vector2* right = transform->position;
		if (right->x < 710)
		{
			right->x += 4;
			transform->position = right;
		}
	}
}
