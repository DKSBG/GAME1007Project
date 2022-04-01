#pragma once
#include "gameObject.h"
#include "tinyxml.h"
#include <map>

bool TransformHandler(Transform* transform, TiXmlElement* pComponentsRoot);

class ComponentParser
{
public:
	virtual bool Parse(GameObject* go, TiXmlElement* componentNode) = 0;
};

class ImageParser : public ComponentParser
{
public:
	bool Parse(GameObject* go, TiXmlElement* componentNode);
};

class ColliderParser : public ComponentParser
{
public:
	bool Parse(GameObject* go, TiXmlElement* componentNode);
};

class ReactableItemParser: public ComponentParser
{
public:
	bool Parse(GameObject * go, TiXmlElement * componentNode);
};

class InfinityScrollMapParser : public ComponentParser
{
public:
	bool Parse(GameObject* go, TiXmlElement* componentNode);
};

class PrefabParser 
{
public:
	GameObject* Parser(std::string prefabName);
	ComponentParser* GetComponentParser(std::string componentName);
	bool ComponentsHandler(GameObject* go, TiXmlElement* pComponentsRoot);
	static PrefabParser* GetInstance();
private:
	std::map<std::string, ComponentParser*> m_componentMap;
	static PrefabParser* m_instance;
};

class CameraParser 
{
public:
	Camera* Parser(std::string cameraName);
	static CameraParser* GetInstance();
private:
	static CameraParser* m_instance;
};

class SceneLoader
{
public:
	void Load(std::string sceneName);
	void ObjectChildHandler(TiXmlElement* childElement, Transform* trs);
	static SceneLoader* GetInstance();
private:
	static SceneLoader* m_instance;
};

