#include "camera.h"

Camera::Camera(std::string name, Transform transform)
{
	this->name = name;
	this->transform.Clone(transform);
}

std::map<std::string, Camera*> CameraManager::GetCameraMap()
{
	return m_cameraMap;
}

CameraManager* CameraManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new CameraManager();
	return m_instance;
}

Camera* CameraManager::CreateCamera(std::string name, Transform transform)
{
	Camera* pCamera = NULL;
	auto it = m_cameraMap.find(name);
	if (it == m_cameraMap.end())
	{
		pCamera = new Camera(name, transform);
		m_cameraMap.insert(std::pair<std::string, Camera*>(name, pCamera));
	}
	return pCamera;
}

Camera* CameraManager::GetCamera(std::string name)
{
	Camera* pCamera = NULL;
	auto it = m_cameraMap.find(name);
	if (it != m_cameraMap.end())
	{
		pCamera = m_cameraMap[name];
	}
	return pCamera;
}

void CameraManager::ClearCamera() 
{
	for (auto cam : m_cameraMap) 
	{
		delete cam.second;
	}
	m_cameraMap.clear();
}

CameraManager* CameraManager::m_instance = NULL;