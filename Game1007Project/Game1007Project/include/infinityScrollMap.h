#pragma once
#include "gameObject.h"
#include "camera.h"

class InfinityScrollMap : GOComponent
{
public:
	void Update();
	int moveSpeed;
	Transform* mapCam;
	Transform* mapL;
	Transform* mapR;
private:
	float m_accumulateMovePixel;
};