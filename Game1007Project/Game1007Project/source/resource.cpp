#include"resource.h"
#include"game.h"

#pragma region ResourceManager Implement
ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	m_pRenderer = renderer;
}

TextureResource* ResourceManager::LoadTexture(string texturePath)
{
	//size_t id = pathHash(texturePath);
	TextureResource* resource;

	//if (m_textureResourceMap.find(id) == m_textureResourceMap.end())
	if (m_textureResourceMap.find(texturePath) == m_textureResourceMap.end())
	{
		SDL_Surface* pSurface = IMG_Load((TEXTUREPATH + texturePath).c_str());

		if (pSurface == NULL) 
		{
			printf("Unable to load bitmap: %s\n", SDL_GetError());
			return NULL;
		};

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
		SDL_FreeSurface(pSurface);
		resource = new TextureResource(pTexture);
		//resource->DestroyCallback = TextureResourceCollect;
		//m_textureResourceMap.insert(pair<size_t, TextureResource*>(id, resource));
		m_textureResourceMap.insert(pair<string, TextureResource*>(texturePath, resource));
	}
	else
	{
		//resource = m_textureResourceMap[id];
		resource = m_textureResourceMap[texturePath];
	}
	return resource;
}

/*void ResourceManager::TextureResourceCollect(int id)
{
	map<size_t, TextureResource*>::iterator it = m_textureResourceMap.find(id);
	if (it != m_textureResourceMap.end())
	{
		TextureResource* resource = m_textureResourceMap[id];
		m_textureResourceMap.erase(it);
		SDL_DestroyTexture(resource->pTexture);
		delete resource;
	}
}*/

ResourceManager* ResourceManager::GetInstance() 
{
	if (s_pInstance == nullptr) 
	{
		s_pInstance = new ResourceManager(Game::GetInstance()->GetRenderer());
	}
	return s_pInstance;
}

ResourceManager* ResourceManager::s_pInstance = nullptr;
#pragma endregion

#pragma region TextureResource
TextureResource::TextureResource(SDL_Texture* pTexture) 
{
	this->pTexture = pTexture;
}

TextureResource::~TextureResource() 
{

}
#pragma endregion






