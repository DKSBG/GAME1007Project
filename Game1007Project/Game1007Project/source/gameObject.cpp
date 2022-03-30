#include "gameObject.h"
#include "image.h"
#include "animation.h"
#include "collider.h"
#include "colliderManager.h"
#include "transform.h""
#include <exception>

using namespace std;

Transform::~Transform()
{
	//if (position != NULL)
	//	delete position;
	//if (size != NULL)
	//	delete size;
	//if (scale != NULL)
	//	delete scale;
}

void Transform::Clone(const Transform target)
{
	position.x = target.position.x;
	position.y = target.position.y;
	size.x = target.size.x;
	size.y = target.size.y;
	scale.x = target.scale.x;
	scale.y = target.scale.y;
}

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
	if (find(m_newGameObjectList.begin(), m_newGameObjectList.end(), go) == m_newGameObjectList.end())
		this->m_newGameObjectList.push_back(go);
}

void GameObjectManager::PopGameObject(GameObject* go)
{
	if (find(m_deleteGameObjectList.begin(), m_deleteGameObjectList.end(), go) == m_deleteGameObjectList.end())
	{
		m_deleteGameObjectList.push_back(go);
		Collider* collider = go->GetComponent<Collider>();

		if(collider!= NULL)
			CollideManager::GetInstanse()->RemoveCollider(collider->colliderInfo);

	}
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

	for (int index = m_deleteGameObjectList.size() - 1; index >= 0; index --)
	{
		auto it = std::find(m_gameObjectList.begin(), m_gameObjectList.end(), m_deleteGameObjectList[index]);
		m_gameObjectList.erase(it);
		delete m_deleteGameObjectList[index];
	}

	m_deleteGameObjectList.clear();
	m_newGameObjectList.clear();
}
#pragma endregion

#pragma region GameObject Implement
GameObject::GameObject()
{
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

void GameObject::OnCollide(GameObject* go)
{
	for (auto componentPair : m_componentMap)
	{
		GOComponent* goComponent = (GOComponent*)componentPair.second;
		goComponent->OnCollide(go);
	}
}
#pragma endregion

#pragma region Transform Implement
Transform::Transform()
{
	this->position.Set(0, 0);
	this->scale.Set(1, 1);
	this->size.Set(10, 10);
}
#pragma endregion





