#pragma once
#include "reactableItem.h"
#include "gun.h"

class Follower : public Ship
{
public:
	void Update();
	void Attack();
private:
	Gun* m_pGun;
};

class PlayerShip : public Ship
{
public:
	void Update();
	void Init();
	void Attack();
	void Move();
	void Invincible();
	void SpecificReact(ReactableItem* giver);
private:
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	float m_lastCamPosX;
	Camera* m_pCam;
	Gun* m_pGun;
	GameObject* m_protector;
	int m_invincibleTimer;
	GameObject* m_follower[2];
	int piece = 1;
};


