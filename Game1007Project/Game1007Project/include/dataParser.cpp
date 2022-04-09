#include<iostream>
#include "image.h"
#include "gameController.h"
#include "collider.h"
#include "reactableItem.h"
#include "infinityScrollMap.h"
#include "dataParser.h"

ComponentParser* PrefabParser::GetComponentParser(std::string componentName)
{
	ComponentParser* parser = NULL;
	auto it = m_componentMap.find(componentName);

	if (it == m_componentMap.end()) 
	{
		if (componentName == "Image")
			parser = new ImageParser();
		else if (componentName == "Collider")
			parser = new ColliderParser();
		else if (componentName == "ReactableItem")
			parser = new ReactableItemParser();
		else if (componentName == "InfinityScrollMap")
			parser = new InfinityScrollMapParser();
		else if (componentName == "GameController")
			parser = new GameControllerParser();
		else
			std::cout << "Load Component Error: Loader doen't support component " << componentName << std::endl;

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

bool TransformHandler(Transform* transform, TiXmlElement* pComponentsRoot)
{
	if(transform == NULL)
		return false;
	if (pComponentsRoot == NULL)
		return true;

	Vector2* targetVector = NULL;

	for (TiXmlElement* element = pComponentsRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string value = element->Value();

		if (value == "Scale")
			targetVector = &transform->scale;
		else if (value == "Position")
			targetVector = &transform->position;
		else if (value == "Size")
			targetVector = &transform->size;
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
			std::cout << "Load Prefab Wrong: Element name not found" << std::endl;
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

	if (TransformHandler(&go->transform, pTrsElement) == false)
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

bool ColliderParser::Parse(GameObject* go, TiXmlElement* componentElement)
{
	if (go == NULL)
		return false;
	go->AddComponent(new Collider());
	return true;
}

bool ImageParser::Parse(GameObject* go, TiXmlElement* componentElement)
{
	std::string layer,texture, nativeSize;
	int layerIndex;

	if (componentElement->Attribute("layer") == NULL)
	{
		std::cout << "Image Component Error: layer attribute not found." << std::endl;
		return false;
	}
	else 
	{
		layer = componentElement->Attribute("layer");
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

	if(componentElement->GetText() == NULL)
	{
		std::cout << "Image Component Error: texture resource not found" << std::endl;
		return false;
	}
	else 
	{
		texture = componentElement->GetText();
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
	nativeSize = componentElement->Attribute("SetNativeSize");
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
	else if (text == "Enemy2Ship")
		item = new Enemy2Ship();
	else if (text == "Turret")
		item = new Turret();
	else if (text == "BoostEnemyShip")
		item = new BoostEnemyShip();
	else if (text == "Obstacle")
		item = new Obstacle();
	else if (text == "StraightProjectile")
		item = new StraightProjectile();
	else
		std::cout << "Load ReactablrItem Wrong: Not handle attribute" << text << std::endl;

	if (item == NULL) 
	{
		std::cout << "ReactableItem Component Error: " << text << "script not found." << std::endl;
		return false;
	}

	go->AddComponent<ReactableItem>(item);
	item->Init();
}

// TODO
bool ReactableItemParser::SubAttributeParse(ReactableItem* item, TiXmlElement* componentElement)
{
	if (item == NULL || componentElement == NULL)
		return false;
	return true;
}

bool InfinityScrollMapParser::Parse(GameObject* go, TiXmlElement* componentElement) 
{
	if (componentElement->Attribute("map") == NULL)
	{
		std::cout << "InfinityScrollMap Component Error: map attribute not found." << std::endl;
		return false;
	}

	InfinityScrollMap* scrollMap = new InfinityScrollMap(componentElement->Attribute("map"));
	go->AddComponent<InfinityScrollMap>(scrollMap);

	if (componentElement->Attribute("camera") != NULL) 
	{
		Camera* p_Cam = CameraManager::GetInstance()->GetCamera(componentElement->Attribute("camera"));
		if (p_Cam != NULL) 
		{
			scrollMap->mapCam = &p_Cam->transform;
		}
	}

	if (componentElement->Attribute("targetCam") != NULL)
	{
		Camera* p_Cam = CameraManager::GetInstance()->GetCamera(componentElement->Attribute("targetCam"));
		if (p_Cam != NULL)
		{
			scrollMap->SetTargetCam(p_Cam);
		}
	}

	if (componentElement->Attribute("moveRate") != NULL)
	{
		float moveRate;
		try
		{
			moveRate = std::stof(componentElement->Attribute("moveRate"));
			scrollMap->moveRate = moveRate;
		}
		catch (exception e)
		{
			std::cout << "InfinityScrollMap Component Error: speed format is wrong." << std::endl;
		}
	}
}

bool GameControllerParser::Parse(GameObject* go, TiXmlElement* componentElement) 
{
	if (go == NULL)
		return false;
	go->AddComponent(new GameController())->Init();
	return true;
}

CameraParser* CameraParser::m_instance = NULL;
CameraParser* CameraParser::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new CameraParser();
	}
	return m_instance;
}

Camera* CameraParser::Parser(std::string cameraName)
{
	TiXmlDocument xmlDoc;
	string filePath = "data/camera/" + cameraName;
	if (!xmlDoc.LoadFile(filePath.c_str()))
	{
		cout << xmlDoc.ErrorDesc() << "(" << cameraName << ")";
		return NULL;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	string name;
	Transform transform;
	std::vector<int> layerVector;

	for (TiXmlElement* element = pRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		std::string value = element->Value() == 0 ? "" : element->Value();
		if (value == "")
		{
			std::cout << "Load Camera Wrong: Element name not found" << std::endl;
			continue;
		}

		if (value == "Name") 
		{
			name = element->GetText();
		}
		else if (value == "Layer") 
		{
			try 
			{
				layerVector.push_back(std::stoi(element->GetText()));
			}
			catch (std::exception e) 
			{
				std::cout << "Load Camera Wrong: Layer data format is wrong." << std::endl;
			}
		}
		else if (value == "FullScreen") 
		{
			transform.size.Set(MainGame::screenW ,MainGame::screenH);
		}
		else if (value == "Transform")
		{
			TransformHandler(&transform, element);
		}
		else 
		{
			std::cout << "Load Camera Wrong: Not handle element " << value << std::endl;
		}
	}

	Camera* pCam = CameraManager::GetInstance()->CreateCamera(name, transform);
	for (int layer : layerVector) 
	{
		CanvasManager::GetInstance()->TryGetCanvas(layer)->SetCamera(pCam);
	}
	return pCam;
}

void SceneLoader::ObjectChildHandler(TiXmlElement* childElement, Transform* trs)
{
	for (TiXmlElement* element = childElement; element != NULL; element = element->NextSiblingElement())
	{
		std::string value = element->Value() == 0 ? "" : element->Value();
		if (value == "")
		{
			std::cout << "Load Scene Wrong: Element name not found" << std::endl;
			continue;
		}

		if (value == "Transform")
		{
			TransformHandler(trs, element);
		}
		else
		{
			std::cout << "Load Scene Wrong: Not handle element " << value << " in child element\n";
		}
	}
}

void SceneLoader::Load(std::string sceneName) 
{
	TiXmlDocument xmlDoc;
	string filePath = "data/scene/" + sceneName;
	if (!xmlDoc.LoadFile(filePath.c_str()))
	{
		cout << xmlDoc.ErrorDesc() << "(" << sceneName << ")";
		return;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	for (TiXmlElement* element = pRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement()) 
	{
		std::string value = element->Value() == 0 ? "" : element->Value();
		if (value == "")
		{
			std::cout << "Load Scene Wrong: Element name not found" << std::endl;
			continue;
		}

		if (value == "Camera" || value == "Prefab")
		{
			Transform *transform = NULL;
			if (element->Attribute("name")) 
			{
				if(value == "Camera")
					transform = &CameraParser::GetInstance()->Parser(element->Attribute("name"))->transform;
				if (value == "Prefab")
					transform = &PrefabParser::GetInstance()->Parser(element->Attribute("name"))->transform;
				ObjectChildHandler(element->FirstChildElement(), transform);
			}
			else 
			{
				std::cout << "Load Scene Wrong: "<< value  <<" element doesn't contain name." << std::endl;
			}
		}
		else
		{
			std::cout << "Load Scene Wrong: Not handle element " << value << std::endl;
		}

	}
}

SceneLoader* SceneLoader::m_instance = NULL;
SceneLoader* SceneLoader::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new SceneLoader();
	}
	return m_instance;
}


