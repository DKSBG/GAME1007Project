#pragma once
#include "gameObject.h"
#include "collideInfo.h"

class CollideManager
{
public:
	void AddCollider(CollideInfo* collider);
	void RemoveCollider(CollideInfo* collider);
	void DetectColliding();
	void RefleshCollideList();
	static CollideManager* GetInstanse();
private:
	vector<CollideInfo*> m_colliderList;
	vector<CollideInfo*> m_newColliderList;
	vector<CollideInfo*> m_removeColliderList;
	static CollideManager* s_instance;
};