#pragma once
#include <map>
#include <vector>
#include <string>
#include <exception>
#include "gameVector.h"
using namespace std;

class Transform {
public:
	Transform();
	Vector2* position;
	Vector2* size;
	Vector2* scale;
};

class GameObjectException : public exception {
public:
	GameObjectException(string reason);
	const char* what() const throw();
private:
	string m_reason;
};

class GameObject{
public:
	GameObject();
	template<typename T>
	T* GetComponent();
	template<typename T>
	T* AddComponent(T* t);

	void Update();
	void Draw();
	Transform* transform;
private:
	std::map<size_t, void*> m_componentMap;
};

class GOComponent 
{
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	GameObject* gameObject;
	Transform* transform;
};

class GameObjectManager {
public:
	void PushGameObject(GameObject* go);
	void PopGameObject(GameObject* go);
	void UpdateAllGameObject();
	void PreDrawAllGameObject();
	static GameObjectManager* GetInstance();
private:
	vector<GameObject*> gameObjectList;
	static GameObjectManager* s_pInstance;
};