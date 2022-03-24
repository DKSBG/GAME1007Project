//#pragma once
//#include"game.h"
//#include"gameObject.h"
//#include"math.h"
//#include"attack.h"
//
//class ExampleShipScript : GOComponent
//{
//public:
//	void Update();
//};
//
//class BasicUnitInfo : public GOComponent
//{
//public:
//	int speed;
//	Vector2 moveVector;
//	int hp = 1;
//	bool isDamageAlly = false;
//	AttackStrategy* attack;
//	virtual void UnderAttack() = 0;
//};
//
//class Ally : public BasicUnitInfo 
//{
//public:
//	void OnCollide(GameObject *go);
//};
//
//class Enemy : public BasicUnitInfo 
//{
//public:
//	void OnCollide(GameObject* go);
//};
//class Third : public BasicUnitInfo 
//{
//public:
//	void OnCollide(GameObject* go);
//};
//
//class PlayerShip : public Ally {
//public:
//	void Init();
//	void UnderAttack();
//	void Update();
//private:
//	const Uint8* m_KeyboardStates = SDL_GetKeyboardState(NULL);
//	long m_attackCD = 250;
//	long m_cdTimer = 0;
//};
//
//class ExampleEnemyShip : public Enemy {
//public:
//	void Init();
//	void UnderAttack();
//	void Update();
//private:
//	long m_attackCD = 500;
//	long m_cdTimer = 0;
//};