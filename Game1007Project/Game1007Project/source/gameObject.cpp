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
	this->m_newGameObjectList.push_back(go);
}

void GameObjectManager::PopGameObject(GameObject* go)
{
	auto it = std::find(this->m_gameObjectList.begin(), this->m_gameObjectList.end(), go);
	if (it != this->m_gameObjectList.end()) 
	{
		this->m_gameObjectList.erase(it);
	}
	delete go;
}

void GameObjectManager::UpdateAllGameObject() 
{
	for (auto go : this->m_gameObjectList) 
	{
		go->Update();
	}
}
void GameObjectManager::PreDrawAllGameObject() 
{
	for (auto go : this->m_gameObjectList)
	{
		go->Draw();
	}
}

void GameObjectManager::RefleshGameObjectList() 
{
	for (auto go : m_newGameObjectList) 
	{
		m_gameObjectList.push_back(go);
	}
	m_newGameObjectList.clear();
}
#pragma endregion

#pragma region GameObject Implement
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





