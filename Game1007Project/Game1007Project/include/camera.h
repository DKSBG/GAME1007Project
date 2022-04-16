#pragma once
#include "transform.h"
#include "gameVector.h"
#include <map>
#include <string>

class Camera
{
public:
	Camera(std::string name, Transform transform);
	std::string name;
	Transform transform;

};

class CameraManager 
{
public:
	static CameraManager* GetInstance();
	Camera* CreateCamera(std::string name, Transform transform);
	Camera* GetCamera(std::string name);
	void ClearCamera();
	std::map<std::string, Camera*> GetCameraMap();
private:
	std::map<std::string, Camera*> m_cameraMap;
	static CameraManager* m_instance;

};

