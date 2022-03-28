#include "camera.h"

Camera::Camera(std::string name, Transform trs)
{
	this->name = name;
	this->trs.Clone(trs);
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

void CameraManager::CreateCamera(std::string name, Transform trs)
{
	auto it = m_cameraMap.find(name);
	if (it == m_cameraMap.end())
	{
		Camera* pCamera = new Camera(name, trs);
		m_cameraMap.insert(std::pair<std::string, Camera*>(name, pCamera));
	}
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

CameraManager* CameraManager::m_instance = NULL;