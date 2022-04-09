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

void InfinityScrollMap::SetTargetCam(Camera* cam) 
{
	m_targetCam = cam;
	m_mainCamLastPosX = cam->transform.position.x;
}

void InfinityScrollMap::Update()
{
	if (mapCam == NULL) 
	{
		cout << "Infinity Scroll Map Error: mapCam is NULL. \n";
		return;
	}

	if (m_targetCam == NULL)
	{
		cout << "Infinity Scroll Map Error: targetCam is NULL. \n";
		return;
	}

	float targetCamMoveDistance = m_targetCam->transform.position.x - m_mainCamLastPosX;

	float movePixel = targetCamMoveDistance * moveRate;
	m_accumulateMovePixel += movePixel;

	if (m_accumulateMovePixel >= m_mapL->size.x * m_mapL->scale.x)
	{
		m_accumulateMovePixel -= m_mapL->size.x * m_mapL->scale.x;
	}

	mapCam->position.x = m_accumulateMovePixel;
	m_mainCamLastPosX = m_targetCam->transform.position.x;
}