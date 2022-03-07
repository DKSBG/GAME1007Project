#include"InputHandler.h"

// Script component no need to draw.
void InputHandler::Draw()
{
	
}
// This metherd is called by engine each frame.
void InputHandler::Update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (m_KeyboardStates[SDL_SCANCODE_W])
			{
				Vector2* up = transform->position;
				up->y -= 5;
				transform->position = up;
				
			}
			if (m_KeyboardStates[SDL_SCANCODE_S])
			{
				Vector2* down = transform->position;
				down->y += 5;
				transform->position = down;
				down->y <= 432;
			}
			if (m_KeyboardStates[SDL_SCANCODE_A])
			{
				Vector2* left = transform->position;
				left->x -= 5;
				transform->position = left;
				left->x >= 0;
			}
			if (m_KeyboardStates[SDL_SCANCODE_D])
			{
				Vector2* right = transform->position;
				right->x += 5;
				transform->position = right;
				right->x <= 768;
			}
			if (m_KeyboardStates[SDL_SCANCODE_SPACE])
			{
				Vector2* bullet = transform->position;
				bullet->x += 5;
				transform->position = bullet;
			}
		case SDL_KEYUP:
			if (!m_KeyboardStates[SDL_SCANCODE_W])
			{
				false;
			}
			if (!m_KeyboardStates[SDL_SCANCODE_S])
			{
				false;
			}
			if (!m_KeyboardStates[SDL_SCANCODE_A])
			{
				false;
			}
			if (!m_KeyboardStates[SDL_SCANCODE_D])
			{
				false;
			}
			break;
		}
	}
}
