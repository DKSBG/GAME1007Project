#include "infinityScrollMap.h"
#include "game.h"

void InfinityScrollMap::Update()
{
	float movePixel = (float)moveSpeed / 1000 * MainGame::deltaTime;
	mapCam->position->x += movePixel;
	m_accumulateMovePixel += movePixel;

	if (m_accumulateMovePixel >= mapL->size->x * mapL->scale->x) 
	{
		m_accumulateMovePixel -= mapL->size->x * mapL->scale->x;
		mapCam->position->x = m_accumulateMovePixel;
	}
}