#include "colliderManager.h"
#include "iostream"

void GetEdge(CollideInfo* collider,float* top, float* bottom, float* right, float* left)
{
	Transform* trs = collider->pGameObject->transform;
	float centerX = trs->position->x + (trs->size->x * trs->scale->x /2);
	float centerY = trs->position->y + (trs->size->y * trs->scale->y / 2);
	float detectH = trs->size->y * trs->scale->y * collider->detectRange->y / 2;
	float detectW = trs->size->x * trs->scale->x * collider->detectRange->x / 2;
	*top = centerY - detectH;
	*bottom = centerY + detectH;
	*right = centerX - detectW;
	*left = centerX + detectW;
}

void CollideManager::AddCollider(CollideInfo* collider)
{
	m_newColliderList.push_back(collider);
}

void CollideManager::RemoveCollider(CollideInfo* collider)
{
	m_removeColliderList.push_back(collider);
}

void CollideManager::DetectColliding()
{
	bool collide = false;
	int len = m_colliderList.size() - 1;
	for (int srcIdx = 0; srcIdx < len; srcIdx++)
	{
		for (int tarIdx = srcIdx + 1; tarIdx < m_colliderList.size(); tarIdx++) 
		{
			float srcTop, srcBottom, srcLeft, srcRight;
			float tarTop, tarBottom, tarLeft, tarRight;
			GetEdge(m_colliderList[srcIdx], &srcTop, &srcBottom, &srcLeft, &srcRight);
			GetEdge(m_colliderList[tarIdx], &tarTop, &tarBottom, &tarLeft, &tarRight);

			if ((tarTop <= srcTop && srcTop <= tarBottom) || (tarTop <= srcBottom && srcBottom <= tarBottom))
				if ((tarLeft <= srcLeft && srcLeft <= tarRight) || (tarLeft <= srcRight && srcRight <= tarRight))
					collide = true;

			if ((srcTop <= tarTop && tarTop <= srcBottom) || (srcTop <= tarBottom && tarBottom <= srcBottom))
				if ((srcLeft <= tarLeft && tarLeft <= srcRight) || (srcLeft <= tarRight && tarRight <= srcRight))
					collide = true;

			if (collide) 
			{
				m_colliderList[srcIdx]->pGameObject->OnCollide(m_colliderList[tarIdx]->pGameObject);
				m_colliderList[tarIdx]->pGameObject->OnCollide(m_colliderList[srcIdx]->pGameObject);
			}
		}
	}
}

void CollideManager::RefleshCollideList() 
{
	for (auto go : m_newColliderList)
	{
		m_colliderList.push_back(go);
	}

	for (int index = m_removeColliderList.size() - 1; index >= 0; index--)
	{
		auto it = std::find(m_colliderList.begin(), m_colliderList.end(), m_removeColliderList[index]);
		m_colliderList.erase(it);
	}

	m_removeColliderList.clear();
	m_newColliderList.clear();
}

CollideManager* CollideManager::GetInstanse()
{
	if (s_instance == NULL)
		s_instance = new CollideManager();
	return s_instance;
}

CollideManager* CollideManager::s_instance = NULL;

