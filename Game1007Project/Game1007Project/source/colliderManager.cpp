#include "colliderManager.h"
#include "iostream"

struct RectInfo
{
	float top, down, right, left;
};

void GetEdge(CollideInfo* collider,float* top, float* bottom, float* right, float* left)
{
	Transform transform;
	transform.Clone(collider->pGameObject->transform);

	float centerX = transform.globalPosition.x + (transform.GetWidth() / 2);
	float centerY = transform.globalPosition.y + (transform.GetHeight() / 2);
	float detectH = transform.GetHeight() * collider->detectRange.y / 2;
	float detectW = transform.GetWidth() * collider->detectRange.x / 2;
	*top = centerY - detectH;
	*bottom = centerY + detectH;
	*right = centerX - detectW;
	*left = centerX + detectW;
}

void CollideManager::AddCollider(CollideInfo* collider)
{
	if (find(m_removeColliderList.begin(), m_removeColliderList.end(), collider) == m_removeColliderList.end())
		m_newColliderList.push_back(collider);
}

void CollideManager::RemoveCollider(CollideInfo* collider)
{
	if(find(m_removeColliderList.begin(), m_removeColliderList.end(),collider) == m_removeColliderList.end())
		m_removeColliderList.push_back(collider);
}

void CollideManager::DetectColliding()
{
	bool collide = false;
	int len = m_colliderList.size() - 1;
	for (int srcIdx = 0; srcIdx < len; srcIdx++)
	{
		if (m_colliderList[srcIdx]->pGameObject->isActive == false)
			continue;

		for (int tarIdx = srcIdx + 1; tarIdx < m_colliderList.size(); tarIdx++) 
		{
			if (m_colliderList[tarIdx]->pGameObject->isActive == false)
				continue;

			collide = false;
			RectInfo rect1, rect2, rectVDown, rectVTop, rectHLeft, rectHRight;
			GetEdge(m_colliderList[srcIdx], &rect1.top, &rect1.down, &rect1.left, &rect1.right);
			GetEdge(m_colliderList[tarIdx], &rect2.top, &rect2.down, &rect2.left, &rect2.right);

			rectVTop = (rect1.top <= rect2.top) ? rect1 : rect2;
			rectVDown = (rect1.top > rect2.top) ? rect1 : rect2;
			rectHLeft = (rect1.left <= rect2.left) ? rect1 : rect2;
			rectHRight = (rect1.left > rect2.left) ? rect1 : rect2;

			if(rectVTop.down >= rectVDown.top && rectHLeft.right >= rectHRight.left)
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

