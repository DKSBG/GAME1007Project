#pragma once
#include "gameObject.h"
#include "tinyxml.h"
#include <map>

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


class PrefabParser 
{
public:
	GameObject* Parser(std::string prefabName);
	ComponentParser* GetComponentParser(std::string componentName);
	bool ComponentsHandler(GameObject* go, TiXmlElement* pComponentsRoot);
	bool TransformHandler(GameObject* go, TiXmlElement* pComponentsRoot);
	static PrefabParser* GetInstance();
private:
	std::map<std::string, ComponentParser*> m_componentMap;
	static PrefabParser* m_instance;
};

