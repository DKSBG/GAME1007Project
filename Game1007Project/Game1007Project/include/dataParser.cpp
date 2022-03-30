#include<dataParser.h>
#include<iostream>
#include "image.h"
#include "collider.h"
#include "reactableItem.h"

ComponentParser* PrefabParser::GetComponentParser(std::string componentName)
{
	ComponentParser* parser = NULL;
	auto it = m_componentMap.find(componentName);

	if (it == m_componentMap.end()) 
	{
		if (componentName == "Image")
			parser = new ImageParser();

		if (componentName == "Collider")
			parser =  new ColliderParser();

		if (componentName == "ReactableItem")
			parser =  new ReactableItemParser();

		if (parser != NULL) 
			m_componentMap.insert(std::pair<std::string, ComponentParser*>(componentName, parser));

		return parser;
	}
	else
	{
		return m_componentMap[componentName];
	}
}

bool PrefabParser::ComponentsHandler(GameObject* go, TiXmlElement* pComponentsRoot)
{
	if (go == NULL)
		return false;
	if (pComponentsRoot == NULL)
		return true;

	for (TiXmlElement* element = pComponentsRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		ComponentParser* parser = GetComponentParser(element->Value());
		if (parser != NULL)
		{
			parser->Parse(go, element);
		}
		else
		{
			std::cout << "Load Prefab Error: compenent type " << element->Value() << " not found." << std::endl;
			return false;
		}
	}
	return true;
}

bool PrefabParser::TransformHandler(GameObject* go, TiXmlElement* pComponentsRoot)
{
	if(go == NULL)
		return false;
	if (pComponentsRoot == NULL)
		return true;

	Vector2* targetVector = NULL;

	for (TiXmlElement* element = pComponentsRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string value = element->Value();

		if (value == "Scale")
			targetVector = &go->transform.scale;
		else if (value == "Position")
			targetVector = &go->transform.position;
		else if (value == "Size")
			targetVector = &go->transform.size;
		else
			targetVector = NULL;

		if (targetVector != NULL) 
		{
			try 
			{
				targetVector->x = std::stof(element->Attribute("x"));
				targetVector->y = std::stof(element->Attribute("y"));
			}
			catch (std::exception e)
			{
				std::cout << "Set Prefab Transform Error: Element " << element->Value() << " attribute is wrong." << std::endl;
				return false;
			}
		}
	}
	return true;
}

GameObject* PrefabParser::Parser(std::string prefabName)
{
	GameObject* go;
	TiXmlDocument xmlDoc;
	string filePath = "data/prefab/" + prefabName;
	if (!xmlDoc.LoadFile(filePath.c_str()))
	{
		cout << xmlDoc.ErrorDesc();
		return NULL;
	}

	go = new GameObject();
	TiXmlElement* pRoot = xmlDoc.RootElement();
	TiXmlElement* pComponentElement = NULL;
	TiXmlElement* pTrsElement = NULL;
	for (TiXmlElement* elememt = pRoot->FirstChildElement(); elememt != NULL; elememt = elememt->NextSiblingElement())
	{
		std::string value = elememt->Value()==0 ? "" : elememt->Value();
		if (value == "")
		{
			std::cout << "Load Prefab Wrong: compenent name not found" << std::endl;
			continue;
		}

		if (value == "Components" && pComponentElement == NULL)
			pComponentElement = elememt;

		if (value == "Transform" != NULL && pTrsElement == NULL)
			pTrsElement = elememt;
	}

	if (ComponentsHandler(go, pComponentElement) == false) 
	{
		if (go != NULL) 
			delete go;
		return NULL;
	}

	if (TransformHandler(go, pTrsElement) == false)
	{
		if (go != NULL)
			delete go;
		return NULL;
	}

	if(pTrsElement)
	return go;
}

PrefabParser* PrefabParser::GetInstance() 
{
	if (m_instance == NULL)
		m_instance = new PrefabParser();
	return m_instance;
}

PrefabParser* PrefabParser::m_instance = NULL;

bool ColliderParser::Parse(GameObject* go, TiXmlElement* componentNode) 
{
	if (go == NULL)
		return false;
	go->AddComponent(new Collider());
	return true;
}

bool ImageParser::Parse(GameObject* go, TiXmlElement* componentNode)
{
	std::string layer,texture, nativeSize;
	int layerIndex;

	if (componentNode->Attribute("layer") == NULL)
	{
		std::cout << "Image Component Error: layer attribute not found." << std::endl;
		return false;
	}
	else 
	{
		layer = componentNode->Attribute("layer");
		try
		{
			layerIndex = std::stoi(layer);
		}
		catch (exception e)
		{
			std::cout << "Image Component Error: layer format is wrong." << std::endl;
			return false;
		}
	}

	if(componentNode->GetText() == NULL)
	{
		std::cout << "Image Component Error: texture resource not found" << std::endl;
		return false;
	}
	else 
	{
		texture = componentNode->GetText();
	}

	for (auto c : layer) 
	{
		if (c > '9' && c < '0') 
		{
			std::cout << "Image Component Error: layer attribe is wrong data type" << std::endl;
			return false;
		}
	}

	Image* img = new Image(texture, layerIndex);
	go->AddComponent<Image>(img);
	nativeSize = componentNode->Attribute("SetNativeSize");
	if (nativeSize == "true")
	{
		img->SetNativeSize();
	}

	return true;
}

bool ReactableItemParser::Parse(GameObject* go, TiXmlElement* componentElement)
{
	std::string text = componentElement->GetText();
	ReactableItem* item = NULL;

	if (text == "PlayerShip")
		item = new PlayerShip();
	else if (text == "Enemy1Ship")
		item = new Enemy1Ship();
	else if (text == "Obstacle")
		item = new Obstacle();

	if (item == NULL) 
	{
		std::cout << "ReactableItem Component Error: " << text << "script not found." << std::endl;
		return false;
	}

	go->AddComponent<ReactableItem>(item);
	item->Init();
}
