#include"gameObject.h"
#include"image.h"
#include"animation.h"
#include <exception>

using namespace std;

#pragma region Exception
GameObjectException::GameObjectException(string reason)
{
	m_reason = reason;
}

const char* GameObjectException::what() const throw()
{
	return m_reason.c_str();
}
#pragma endregion

#pragma region  GameObjectManager Implement
GameObjectManager* GameObjectManager::s_pInstance = nullptr;
GameObjectManager* GameObjectManager::GetInstance() 
{
	if (s_pInstance == nullptr) 
	{
		s_pInstance = new GameObjectManager();
	}
	return s_pInstance;
}

void GameObjectManager::PushGameObject(GameObject* go)
{
	this->gameObjectList.push_back(go);
}

void GameObjectManager::PopGameObject(GameObject* go)
{
	auto it = std::find(this->gameObjectList.begin(), this->gameObjectList.end(), go);
	if (it != this->gameObjectList.end()) 
	{
		this->gameObjectList.erase(it);
	}
	delete go;
}
void GameObjectManager::UpdateAllGameObject() 
{
	for (auto go : this->gameObjectList) 
	{
		go->Update();
	}
}
void GameObjectManager::PreDrawAllGameObject() 
{
	for (auto go : this->gameObjectList)
	{
		go->Draw();
	}
}
#pragma endregion

#pragma region GameObject Implement
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

template Image* GameObject::AddComponent(Image* t);
template Animation* GameObject::AddComponent(Animation* t);

GameObject::GameObject()
{
	this->transform = new Transform();
	GameObjectManager::GetInstance()->PushGameObject(this);
}

void GameObject::Draw()
{
	for (auto componentPair : m_componentMap)
	{
		GOComponent* goComponent = (GOComponent*)componentPair.second;
		goComponent->Draw();
	}
}

void GameObject::Update()
{
	for (auto componentPair : m_componentMap)
	{
		GOComponent* goComponent = (GOComponent*)componentPair.second;
		goComponent->Update();
	}
}
#pragma endregion

#pragma region Transform Implement
Transform::Transform()
{
	this->position = new Vector2(0, 0);
	this->scale = new Vector2(1, 1);
	this->size = new Vector2(10, 10);
}
#pragma endregion





