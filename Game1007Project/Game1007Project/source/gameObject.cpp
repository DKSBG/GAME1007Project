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





