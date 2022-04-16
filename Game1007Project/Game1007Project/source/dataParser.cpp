#include<iostream>
#include "image.h"
#include "gameController.h"
#include "collider.h"
#include "reactableItem.h"
#include "playerShip.h"
#include "enemyShip.h"
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
		else if (componentName == "Gun")
			parser = new GunParser();
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

bool PrefabParser::ChildHandler(GameObject* go, TiXmlElement* pComponentsRoot) 
{
	if (go == NULL)
		return false;
	if (pComponentsRoot == NULL)
		return true;

	for (TiXmlElement* element = pComponentsRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{

		std::string value = element->Value() == 0 ? "" : element->Value();
		if (value == "")
		{
			std::cout << "Load Scene Wrong: Element name not found" << std::endl;
			continue;
		}

		if (value == "Prefab")
		{
			GameObject* child = PrefabParser::GetInstance()->Parser(element->Attribute("name"));
			Transform* transform = &child->transform;
 			ObjectChildHandler(element->FirstChildElement(), transform);
			child->_SetParentImmediately(go);
		}
	}

	return true;
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
			targetVector = &transform->localPosition;
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

bool ReactAttributeHandler(ReactAttribute* attr, TiXmlElement* pComponentsRoot)
{
	if (attr == NULL)
		return false;
	if (pComponentsRoot == NULL)
		return true;

	ReactAttribute result;

	for (TiXmlElement* element = pComponentsRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string value = element->Value();

		if (!element->Attribute("val"))
			return false;

		string text = element->Attribute("val");

		if (value == "Fiction") 
		{
			if (text == "Ally")
				result.fiction = Fiction::Ally;
			if (text == "Enemy")
				result.fiction = Fiction::Enemy;
			if (text == "ThridPart")
				result.fiction = Fiction::ThridPart;
		}

		if (value == "ReactTarget")
		{
			if (text == "Both")
				result.target = ReactTarget::Both;
			if (text == "AllyOnly")
				result.target = ReactTarget::AllyOnly;
			if (text == "EnemyOnly")
				result.target = ReactTarget::EnemyOnly;
		}
		else if (value == "ReactType")
		{
			if (text == "HP")
				result.type = ReactType::HP;
			if (text == "Speed")
				result.type = ReactType::Speed;
			if (text == "Atk")
				result.type = ReactType::Atk;
		}
		else if (value == "ReactValue")
		{
			try
			{
				result.reactValue = std::stof(text);
			}
			catch (std::exception e)
			{
				std::cout << "Set ReactalbAttribute Error: Element " << element->Value() << " is wrong." << std::endl;
				return false;
			}
		}
	}

	*attr = result;
	return true;
}

bool ItemAttributeHandler(ItemAttribute* attr, TiXmlElement* pComponentsRoot) 
{
	if (attr == NULL)
		return false;
	if (pComponentsRoot == NULL)
		return true;

	ItemAttribute result;

	for (TiXmlElement* element = pComponentsRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string value = element->Value();

		if (value == "Vector") 
		{
			try
			{
				result.vector.Set(std::stof(element->Attribute("x")), std::stof(element->Attribute("y")));
			}
			catch (std::exception e)
			{
				std::cout << "Set ItemAttribute Error: Element " << element->Value() << " is wrong." << std::endl;
				return false;
			}
		}
		else 
		{
			string text = element->Attribute("val");
			if (value == "Hp")
			{
				try
				{
					result.hp = std::stof(text);
				}
				catch (std::exception e)
				{
					std::cout << "Set ItemAttribute Error: Element " << element->Value() << " is wrong." << std::endl;
					return false;
				}
			}
			else if (value == "Speed")
			{
				try
				{
					result.speed = std::stof(text);
				}
				catch (std::exception e)
				{
					std::cout << "Set ItemAttribute Error: Element " << element->Value() << " is wrong." << std::endl;
					return false;
				}
			}
			else if (value == "Atk")
			{
				try
				{
					result.atk = std::stof(text);
				}
				catch (std::exception e)
				{
					std::cout << "Set ItemAttribute Error: Element " << element->Value() << " is wrong." << std::endl;
					return false;
				}
			}
		}
	}

	*attr = result;
	return true;
}

bool ObjectChildHandler(TiXmlElement* childElement, Transform* trs)
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
	TiXmlElement* pChildElement = NULL;

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

		if (value == "Children" != NULL && pChildElement == NULL)
			pChildElement = elememt;
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

	if (ChildHandler(go, pChildElement) == false)
	{
		if (go != NULL)
			delete go;
		return NULL;
	}

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

	Collider* collider = new Collider();

	for (TiXmlElement* element = componentElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		std::string value = element->Value();
		if (value == "Range") 
		{
			try
			{
				collider->colliderInfo.detectRange.x = std::stof(element->Attribute("x"));
				collider->colliderInfo.detectRange.y = std::stof(element->Attribute("y"));
			}
			catch (std::exception e)
			{
				std::cout << "Set Prefab Transform Error: Element " << element->Value() << " attribute is wrong." << std::endl;
				return false;
			}
		}
	}

	go->AddComponent(collider);
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

bool GunParser::Parse(GameObject* go, TiXmlElement* componentElement) 
{
	Gun* gun = new Gun();
	ReactAttribute rectAttr;
	ItemAttribute attr;
	int cdTime = 0;
	std::string projectile, sound;

	for (TiXmlElement* element = componentElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string value = element->Value();
		if (value == "ReactAttribute") 
		{
			ReactAttributeHandler(&rectAttr, element);
		}
		else if (value == "ItemAttribute") 
		{
			ItemAttributeHandler(&attr, element);
		}
		else 
		{
			if (element->Attribute("val")) 
			{
				if (value == "Projectile")
				{
					projectile = element->Attribute("val");
				}
				else if(value == "Sound") 
				{
					sound = element->Attribute("val");
				}

				if (value == "CDTime") 
				{
					try
					{
						cdTime = std::stof(element->Attribute("val"));
					}
					catch (std::exception e)
					{
						std::cout << "Set Gun Component Error: Element " << element->Value() << " is wrong." << std::endl;
						return false;
					}
				}
			}
		}
	}

	gun->GunAttributeSet(rectAttr, attr);
	gun->GunTypeSet(projectile, sound);
	gun->SetCDTime(cdTime);
	go->AddComponent<Gun>(gun);
}

bool ReactableItemParser::Parse(GameObject* go, TiXmlElement* componentElement)
{
	if (!componentElement->Attribute("val"))
		return false;
	std::string value = componentElement->Attribute("val");
	ReactableItem* item = NULL;

	if (value == "PlayerShip")
		item = new PlayerShip();
	else if (value == "BasicShootEnemy")
		item = new BasicShootEnemy();
	else if (value == "ShootEnemy2")
		item = new ShootEnemy2;
	else if (value == "Turret")
		item = new Turret();
	else if (value == "BoostEnemyShip")
		item = new BoostEnemyShip();
	else if (value == "Obstacle")
		item = new Obstacle();
	else if (value == "StraightProjectile")
		item = new StraightProjectile();
	else if (value == "BossShip")
		item = new BossShip();
	else
		std::cout << "Load ReactablrItem Wrong: Not handle attribute" << value << std::endl;

	if (item == NULL) 
	{
		std::cout << "ReactableItem Component Error: " << value << "script not found." << std::endl;
		return false;
	}

	ReactAttribute rectAttr;
	ItemAttribute attr;

	for (TiXmlElement* element = componentElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string value = element->Value();
		if (value == "ReactAttribute")
		{

			ReactAttributeHandler(&rectAttr, element);
		}
		else if (value == "ItemAttribute")
		{

			ItemAttributeHandler(&attr, element);
		}
	}

	item->itemAttribute = attr;
	item->reactAttrbute = rectAttr;
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
	go->AddComponent(new GameController());
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


