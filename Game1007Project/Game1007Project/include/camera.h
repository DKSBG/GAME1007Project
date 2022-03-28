#pragma once
#include "transform.h"
#include "gameVector.h"
#include <map>
#include <string>

class Camera
{
public:
	Camera(std::string name, Transform trs);
	std::string name;
	Transform trs;

};

class CameraManager 
{
public:
	static CameraManager* GetInstance();
	void CreateCamera(std::string name, Transform trs);
	Camera* GetCamera(std::string name);
	std::map<std::string, Camera*> GetCameraMap();
private:
	std::map<std::string, Camera*> m_cameraMap;
	static CameraManager* m_instance;

};

