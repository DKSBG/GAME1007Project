#pragma once
#include<map>
#include<vector>
#include"resource.h"
#include"gameVector.h"
#include"gameObject.h"
#include"camera.h"

using namespace std;

class DrawingUnit {
public:
	Transform tranform;
	Vector2 ScreenPos;
	SDL_Texture* pTexture;
	SDL_Rect srcRect;
};

class Canvas {
public:
	void SetDrawUnit(DrawingUnit* unit);
	void SetCamera(Camera* pCam);
	Camera* GetCamera();
	void Draw();
private:
	vector<DrawingUnit*> m_drawUnitList;
	Camera* m_pCamera;
};

class CanvasManager {
public:
	Canvas* TryGetCanvas(int layer);
	void Draw();
	//void RegisterDrawDelegate();
	static CanvasManager* GetInstance();
private :
	map<int, Canvas*> m_canvasMap;
	static CanvasManager* s_pInstance;
};



