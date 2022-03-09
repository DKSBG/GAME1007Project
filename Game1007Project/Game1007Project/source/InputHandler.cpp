#include"InputHandler.h"
#include "gameVector.h"
#include "game.h"
#include "script.h"


// Script component no need to draw.
void InputHandler::Draw()
{

}

// This metherd is called by engine each frame.
void InputHandler::Update()
{
	for (int i = 0; i < 322; i++) 
	{ // init them all to false
		KEYS[i] = false;
	}
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		if (event.type == SDL_KEYDOWN)
		{
			KEYS[event.key.keysym.sym] = true;
		}
		else if (event.type == SDL_KEYUP)
		{
			KEYS[event.key.keysym.sym] = false;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_W])
	{
		Vector2* up = transform->position;
		if (up->y > 0)
		{
			up->y -= 5;
			transform->position = up;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_S])
	{
		Vector2* down = transform->position;
		if (down->y < 405)
		{
			down->y += 5;
			transform->position = down;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_A])
	{
		Vector2* left = transform->position;
		if (left->x > 0)
		{
			left->x -= 5;
			transform->position = left;
		}
	}
	if (m_KeyboardStates[SDL_SCANCODE_D])
	{
		Vector2* right = transform->position;
		if (right->x < 710)
		{
			right->x += 5;
			transform->position = right;
		}
	}
	if (KEYS[SDLK_SPACE])
	{
		Image* pImg;
		GameObject* pGoMainShipBullet = new GameObject();
		pImg = new Image("MainShipBullet.png", 4);
		pGoMainShipBullet->AddComponent<Image>(pImg);
		pGoMainShipBullet->GetComponent<Image>()->SetNativeSize();
		Transform* bulletTransform = pGoMainShipBullet->transform;
		bulletTransform->scale = new Vector2(2, 2);
		bulletTransform->position->x = this->transform->position->x;
		bulletTransform->position->y = this->transform->position->y;
		bulletTransform->position->x += this->transform->size->x * this->transform->scale->x;
		bulletTransform->position->y += bulletTransform->size->x * bulletTransform->scale->x;
		bulletTransform->position->y -= (bulletTransform->size->y * bulletTransform->scale->y) / 2;
		
		ExampleProjectileScript *pProjectileScrip = new ExampleProjectileScript();
		Vector2 flyVector;
		flyVector.x = 10;
		flyVector.y = 0;
		pProjectileScrip->SetFlyVector(flyVector);
		pGoMainShipBullet->AddComponent<ExampleProjectileScript>(pProjectileScrip);
	}
	else
	{
		false;
	}
}
