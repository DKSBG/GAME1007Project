#pragma once
#include "gameObject.h"
#include "collider.h"
#include "game.h"
#include "image.h"


enum Camp {Ally, Enemy, ThridPart};
enum ReactCamp { Both, AllyOnly, EnemyOnly };
enum ReactType { HP, Speed, Atk };

struct ReactAttribute
{
	Camp camp = Ally;
	ReactCamp target = Both;
	ReactType type = HP;
	int reactValue;
};

struct ItemAttribute
{
	int hp;
	// Speed unit is pixels per second.
	int speed;
	int atk;
	Vector2* vector;
};

class ReactableItem : public GOComponent 
{
public:
	ReactAttribute reactAttrbute;
	ItemAttribute attribute;
	void Init();
	void Update();
	void OnCollide(GameObject* go);
	void Reacting(ReactAttribute giverAttr);
	virtual void OnDie() = 0;
	virtual void SpecificReact(ReactAttribute giverAttr) = 0;
};

class Projectile : public ReactableItem
{
	void Update();
	void OnDie();
	void SpecificReact(ReactAttribute giverAttr);
};

class StraightProjectile : public Projectile
{
	void Update();
};

class ShootStrategy
{
public:
	virtual void Fire(Transform* attacker, ItemAttribute attr, ReactAttribute reactAttr) = 0;
};

class SingleLineShooting : public ShootStrategy
{
public:
	void Fire(Transform* attacker, ItemAttribute attr, ReactAttribute reactAttr);
};

class SectorShooting : public ShootStrategy
{
public:
	void Fire(Transform* attacker, ItemAttribute attr, ReactAttribute reactAttr);
};

class Ship : public ReactableItem
{
public:
	ShootStrategy* fire;
	void OnDie();
	void SpecificReact(ReactAttribute giverAttr) {}
protected:
	int m_attackCD = 250;
	int m_cdTimer = 0;
	ShootStrategy *m_shooting = NULL;
	Image *m_pImg;
};

class PlayerShip : public Ship 
{
public:
	void Update();
	void Init();
private:
	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
	float m_lastCamPosX;
	Camera* m_pCam;
};

class Enemy1Ship : public Ship
{
public:
	void Update();
	void Init();
private:
	Vector2 m_moveVector;
};

class Obstacle : public ReactableItem
{
	void Init();
	void OnDie();
	void SpecificReact(ReactAttribute giverAttr);
};