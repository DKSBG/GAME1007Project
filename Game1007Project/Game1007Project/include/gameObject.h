#pragma once
#include <map>
#include <vector>
#include <string>
#include <exception>
#include "gameVector.h"
#include "transform.h"

using namespace std;

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
	void OnCollide(GameObject* go);
	void GetPositionModified(Vector2* pos);
	void GetScaleModified(Vector2* scaleRate);

	GameObject* GetParent();
	void SetParent(GameObject* parent);
	GameObject* GetChild(std::string, GameObject* go);
	std::vector<GameObject*> GetChildren();

	// PushChild and PopChild only for GameObjectMamager use.
	void _PushChild(GameObject* child);
	void _PopChild(GameObject* parent);

	Transform transform;
	std::string name;
	bool isActive = true;

private:
	std::map<size_t, void*> m_componentMap;
	std::map<size_t, void*> m_collideHandlerMap;
	GameObject* m_pParent = NULL;
	std::vector<GameObject*> m_pChildren;
	Vector2 m_modifiedPosition;
	Vector2 m_modifiedScaleRate;
};

struct ParentModifiedInfo
{
	GameObject* currentParent;
	GameObject* newParent;
	GameObject* child;
};

class Component 
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void OnCollide(GameObject* go) = 0;
	GameObject* gameObject;
	Transform* transform;
};

class GOComponent : public Component
{
public:
	void Init() {};
	void OnCollide(GameObject* go) {};
	void Draw() {};
	void Update() {};
};

class GameObjectManager {
public:
	void PushGameObject(GameObject* go);
	void PopGameObject(GameObject* go);
	void PopAllGameObject();
	void UpdateAllGameObject();
	void PreDrawAllGameObject();
	void RefleshGameObjectList();
	void ModifiedGameObjectRelationship(ParentModifiedInfo info);
	void RefleshGameObjectRelationship();
	static GameObjectManager* GetInstance();
private:
	vector<GameObject*> m_gameObjectListRootList;
	vector<GameObject*> m_newGameObjectList;
	vector<GameObject*> m_deleteGameObjectList;
	vector<ParentModifiedInfo> m_parentModifiedList;
	void PopGameObjectRoot(GameObject* rootObject);
	static GameObjectManager* s_pInstance;
};

template<typename T>
T* GameObject::GetComponent()
{
	size_t componentHash = (typeid(T*).hash_code());
	if (m_componentMap.find(componentHash) == m_componentMap.end())
		return NULL;
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
	goComponent->transform = &this->transform;
	goComponent->Init();
	return t;
}
