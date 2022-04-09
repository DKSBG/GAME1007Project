#pragma once
#include "gameObject.h"
#include "camera.h"

class InfinityScrollMap : GOComponent
{
public:
	InfinityScrollMap(std::string prefabName);
	void Update();
	void SetTargetCam(Camera* cam);
	float moveRate;
	Transform* mapCam;

private:
	float m_accumulateMovePixel;
	Transform* m_mapL;
	Transform* m_mapR;
	float m_mainCamLastPosX;
	Camera* m_targetCam;
};