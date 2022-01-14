#pragma once
#include<map>
#include<vector>
#include"resource.h"
#include"gameVector.h"
#include"gameObject.h"


using namespace std;

class DrawingUnit {
public:
	TextureResource* resource;
	Transform* tranform;
};

class Canvas {
public:
	void SetDrawUnit(DrawingUnit* unit);
	void Draw();
private:
	vector<DrawingUnit*> m_drawUnitList;
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



