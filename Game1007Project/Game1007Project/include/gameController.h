#pragma once
#include "gameObject.h"
#include "camera.h"

class GameController : public GOComponent
{
public:
	void Init();
	void Update();
private:
	Camera* m_pMainCam;
};