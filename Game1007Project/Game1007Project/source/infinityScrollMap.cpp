#include "infinityScrollMap.h"
#include "game.h"
#include "dataParser.h"

InfinityScrollMap::InfinityScrollMap(std::string prefabName)
{
	GameObject* map = NULL;
	map = PrefabParser::GetInstance()->Parser(prefabName);
	if (map != NULL) 
	{
		m_mapL = &map->transform;
	}

	map = PrefabParser::GetInstance()->Parser(prefabName);
	if (map != NULL)
	{
		m_mapR = &map->transform;
		m_mapR->position.Set(m_mapR->size.x * m_mapR->scale.x, 0);
	}
}

void InfinityScrollMap::Update()
{
	if (mapCam == NULL) 
	{
		cout << "Infinity Scroll Map Error: mapCam is NULL. \n";
		return;
	}

	float movePixel = (float)moveSpeed / 1000 * MainGame::deltaTime;
	mapCam->position.x += movePixel;
	m_accumulateMovePixel += movePixel;

	if (m_accumulateMovePixel >= m_mapL->size.x * m_mapL->scale.x)
	{
		m_accumulateMovePixel -= m_mapL->size.x * m_mapL->scale.x;
		mapCam->position.x = m_accumulateMovePixel;
	}
}