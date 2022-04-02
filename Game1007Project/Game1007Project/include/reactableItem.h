#pragma once
#include "gameObject.h"
#include "collider.h"
#include "game.h"
#include "image.h"


enum class Fiction {Ally, Enemy, ThridPart};
enum class ReactTarget { Both, AllyOnly, EnemyOnly };
enum class ReactType { HP, Speed, Atk };

struct ReactAttribute
{
	Fiction camp = Fiction::Ally;
	ReactTarget target = ReactTarget::Both;
	ReactType type = ReactType::HP;
	int reactValue;
};

struct ItemAttribute
{
	int hp;
	// Speed unit is pixels per second.
	int speed;
	int atk;
	Vector2 vector;
};

class ReactableItem : public GOComponent 
{
public:
	ReactAttribute reactAttrbute;
	ItemAttribute itemAttribute;
	void Init();
	void Update();
	void OnCollide(GameObject* go);
	void Reacting(ReactAttribute giverAttr);
	virtual void OnDie() = 0;
	virtual void SpecificReact(ReactAttribute giverAttr) = 0;
};

class Projectile : public ReactableItem
{
public:
	void Init();
	void Update();
	void OnDie();
	void SpecificReact(ReactAttribute giverAttr);
protected:
	Image* m_pImg;
};

class StraightProjectile : public Projectile
{
public:
	void Update();
};

class ShootStrategy
{
public:
	virtual void Fire(const Transform attacker, ItemAttribute attr, ReactAttribute reactAttr, std::string bullet) = 0;
};

class SingleLineShooting : public ShootStrategy
{
public:
	void Fire(const Transform attacker, ItemAttribute attr, ReactAttribute reactAttr, std::string bullet);
};

class SectorShooting : public ShootStrategy
{
public:
	void Fire(const Transform attacker, ItemAttribute attr, ReactAttribute reactAttr, std::string bullet);
};

class Ship : public ReactableItem
{
public:
	ShootStrategy* fire;
	void OnDie();
	void SpecificReact(ReactAttribute giverAttr) {}
protected:
	int m_attackCD = 500;
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
};

class BoostEnemyShip : public Ship
{
public:
	void Update();
	void Init();
private:
	float m_acceleration;
};


class Turret : public Ship
{
public:
	void Update();
	void Init();
};

class Obstacle : public ReactableItem
{
	void Init();
	void OnDie();
	void SpecificReact(ReactAttribute giverAttr);
};