#pragma once
#include "reactableItem.h"
#include "gun.h"

class PlayerShip : public Ship
{
public:
	void Update();
	void Init();
	void Attack();
	void Move();
private:
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	float m_lastCamPosX;
	Camera* m_pCam;
	Gun* m_pGun;
};