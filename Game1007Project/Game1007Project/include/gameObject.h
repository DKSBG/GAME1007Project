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

template<typename T>
T* GameObject::GetComponent()
{
	size_t componentHash = (typeid(T*).hash_code());
	if (m_componentMap.find(componentHash) == m_componentMap.end())
		throw GameObjectException("Cannot find the component from object");
	else
		return (T*)m_componentMap[componentHash];
}

template<typename T>
T* GameObject::AddComponent(T* t)
{
	if (!is_base_of<GOComponent, T>::value)
		throw GameObjectException("Add a non-component class to Gameobject");

	size_t componentHash = (typeid(t).hash_code());
	if (m_componentMap.find(componentHash) == m_componentMap.end())
	{
		m_componentMap.insert(pair<size_t, void*>(componentHash, (void*)t));
	}
	else
	{
		printf("\nThe component is contained.\n");
		return (T*)m_componentMap[componentHash];
	}

	GOComponent* goComponent = (GOComponent*)t;
	goComponent->gameObject = this;
	goComponent->transform = this->transform;
	return t;
}
