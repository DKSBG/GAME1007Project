#include "gameObject.h"
#include "image.h"
#include "animation.h"
#include "collider.h"
#include "colliderManager.h"
#include "transform.h""
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

CollideInfo::CollideInfo()
{
	detectRange.Set(1, 1);
}

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
			CollideManager::GetInstanse()->RemoveCollider(&collider->colliderInfo);

	}
}

void GameObjectManager::PopAllGameObject()
{
	for (auto go : m_gameObjectListRootList) 
	{
		PopGameObject(go);
	}
}

void GameObjectManager::UpdateAllGameObject() 
{
	for (auto go : this->m_gameObjectListRootList) 
	{
		go->Update();
	}
}
void GameObjectManager::PreDrawAllGameObject() 
{
	for (auto go : this->m_gameObjectListRootList)
	{
		go->Draw();
	}
}

void GameObjectManager::_PopGameObjectRoot(GameObject* rootObject)
{
	auto it = std::find(m_gameObjectListRootList.begin(), m_gameObjectListRootList.end(), rootObject);
	if (it != m_gameObjectListRootList.end())
		m_gameObjectListRootList.erase(it);
}

void GameObjectManager::ModifiedGameObjectRelationship(ParentModifiedInfo info)
{
	m_parentModifiedList.push_back(info);
}

void GameObjectManager::RefleshGameObjectRelationship()
{
	for (auto info : m_parentModifiedList) 
	{
		if (info.currentParent != NULL)
			info.currentParent->_PopChild(info.child);
		else
			_PopGameObjectRoot(info.child);

		if (info.newParent != NULL)
			info.newParent->_PushChild(info.child);
		else
			m_gameObjectListRootList.push_back(info.child);
	}

	m_parentModifiedList.clear();
}

void GameObjectManager::RefleshGameObjectList() 
{
	for (auto go : m_newGameObjectList) 
	{
		if(go->GetParent() == NULL)
			m_gameObjectListRootList.push_back(go);
	}

	for (int index = m_deleteGameObjectList.size() - 1; index >= 0; index --)
	{
		auto it = std::find(m_gameObjectListRootList.begin(), m_gameObjectListRootList.end(), m_deleteGameObjectList[index]);
		m_gameObjectListRootList.erase(it);
		delete m_deleteGameObjectList[index];
		m_deleteGameObjectList[index] == NULL;
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
	if (!isActive)
		return;

	for (auto componentPair : m_componentMap)
	{
		GOComponent* goComponent = (GOComponent*)componentPair.second;
		goComponent->Draw();
	}

	for (auto child : m_pChildren) 
	{
		child->Draw();
	}
}

void GameObject::Update()
{
	if (!isActive)
		return;

	m_modifiedPosition.Set(0, 0);
	if (m_pParent != NULL) 
	{
		Vector2 parentMove, parentScaleRate;
		m_pParent->GetPositionModified(&parentMove);
		m_pParent->GetScaleModified(&parentScaleRate);
		transform.ParentUpdatePostion(parentMove);
		//transform.ParentUpdateScale(parentScaleRate);
	}

	transform.UpdatePostion(&m_modifiedPosition);
	//transform.UpdateScale(&m_modifiedScaleRate);

	for (auto componentPair : m_componentMap)
	{
		GOComponent* goComponent = (GOComponent*)componentPair.second;
		goComponent->Update();
	}

	for (auto child : m_pChildren) 
	{
		child->Update();
	}
}

void GameObject::GetPositionModified(Vector2* pos)
{
	pos->x = m_modifiedPosition.x;
	pos->y = m_modifiedPosition.y;
}

void GameObject::GetScaleModified(Vector2* scaleRate)
{
	scaleRate->x = m_modifiedScaleRate .x;
	scaleRate->y = m_modifiedScaleRate.y;
}

GameObject* GameObject::GetParent() 
{
	return m_pParent;
}

void GameObject::SetParent(GameObject* parent)
{
	ParentModifiedInfo info;
	info.currentParent = m_pParent;
	info.child = this;
	info.newParent = parent;
	GameObjectManager::GetInstance()->ModifiedGameObjectRelationship(info);
	m_pParent = parent;
}

GameObject* GameObject::GetChild(std::string childName, GameObject* go) 
{
	for (auto go : m_pChildren)
	{
		if (go->name == childName)
			return go;
	}
	return NULL;
}

std::vector<GameObject*> GameObject::GetChildren() 
{
	return m_pChildren;
}

void GameObject::_SetParentImmediately(GameObject* parent) 
{
	if(m_pParent != NULL)
		m_pParent->_PopChild(this);
	else
		GameObjectManager::GetInstance()->_PopGameObjectRoot(this);
	m_pParent = parent;
	m_pParent->_PushChild(this);
}

void GameObject::_PushChild(GameObject* child)
{
	m_pChildren.push_back(child);
}

void GameObject::_PopChild(GameObject* child)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), child);
	if (it != m_pChildren.end())
		m_pChildren.erase(it);
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





