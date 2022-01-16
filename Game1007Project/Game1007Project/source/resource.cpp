#include"resource.h"
#include"game.h"

#pragma region ResourceManager Implement
ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	m_pRenderer = renderer;
}

SDL_Texture* ResourceManager::LoadTexture(string locatePath, string filePath)
{
	hash<string> pathHash;
	size_t id = pathHash(filePath);
	SDL_Texture* pTexture;

	if (m_textureMap.find(id) == m_textureMap.end())
	{
		SDL_Surface* pSurface = IMG_Load((locatePath + filePath).c_str());

		if (pSurface == NULL)
		{
			printf("Unable to load bitmap: %s\n", SDL_GetError());
			return NULL;
		};

		pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
		SDL_FreeSurface(pSurface);
		//pTexture->DestroyCallback = TextureResourceCollect;
		m_textureMap.insert(pair<size_t, SDL_Texture*>(id, pTexture));
	}
	else
	{
		pTexture = m_textureMap[id];
	}
	return pTexture;
}

TextureResource* ResourceManager::LoadTextureResource(string texturePath)
{
	hash<string> pathHash;
	size_t id = pathHash(texturePath);
	TextureResource* resource;

	if (m_textureResourceMap.find(id) == m_textureResourceMap.end())
	{
		SDL_Texture* pTexture = this->LoadTexture(TEXTUREPATH, texturePath);
		resource = new TextureResource(pTexture);
		//pTexture->DestroyCallback = TextureResourceCollect;
		m_textureResourceMap.insert(pair<size_t, TextureResource*>(id, resource));
	}
	else
	{
		resource = m_textureResourceMap[id];
	}
	return resource;
}

AtlasResource* ResourceManager::LoadAtlasResource(string texturePath) 
{
	hash<string> pathHash;
	size_t id = pathHash(texturePath);
	AtlasResource* resource;

	if (m_atlasResourceMap.find(id) == m_atlasResourceMap.end())
	{
		SDL_Texture* pTexture = this->LoadTexture(ATLASPATH, texturePath);
		resource = new AtlasResource(pTexture);
		//pTexture->DestroyCallback = TextureResourceCollect;
		m_atlasResourceMap.insert(pair<size_t, AtlasResource*>(id, resource));
	}
	else
	{
		resource = m_atlasResourceMap[id];
	}
	return resource;
}

/*void ResourceManager::TextureResourceCollect(int id)
{
	map<size_t, TextureResource*>::iterator it = m_textureResourceMap.find(id);
	if (it != m_textureResourceMap.end())
	{
		TextureResource* pTexture = m_textureResourceMap[id];
		m_textureResourceMap.erase(it);
		SDL_DestroyTexture(pTexture->m_pTexture);
		delete pTexture;
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

#pragma region TextureKindResource Implement
SDL_Texture* TextureKindResource::GetTexture()
{
	return this->m_pTexture;
}

SDL_Rect TextureKindResource::GetRect()
{
	return this->m_origRect;
}
#pragma endregion


#pragma region TextureResource Implement
TextureResource::TextureResource(SDL_Texture* pTexture) 
{
	this->m_pTexture = pTexture;
	SDL_QueryTexture(this->m_pTexture, NULL, NULL, &m_origRect.w, &m_origRect.h);
}

TextureResource::~TextureResource() 
{

}
#pragma endregion

#pragma region AtlasResource Implement
AtlasResource::AtlasResource(SDL_Texture* pTexture) 
{
	this->m_pTexture = pTexture;
	SDL_QueryTexture(this->m_pTexture, NULL, NULL, &m_origRect.w, &m_origRect.h);
}

AtlasResource::~AtlasResource() 
{

}

void AtlasResource::DefaultSplite() 
{
	this->m_atlasSlot.clear();
	this->m_atlasSlot.push_back(m_origRect);
}

SDL_Rect AtlasResource::GetSlot(int index)
{
	if (index >= m_atlasSlot.size())
		return m_origRect;
	return
		m_atlasSlot.at(index);
}

void AtlasResource::AutoSplite(int row, int col)
{
	SDL_Rect rect;
	rect.w = m_origRect.w / col;
	rect.h = m_origRect.h / row;
	AutoSplite(row, col, rect);
}

void AtlasResource::AutoSplite(int row, int col, SDL_Rect rect)
{
	this->m_atlasSlot.clear();

	for (int colIndex = 0; colIndex < row; colIndex++)
	{
		for (int rowIndex = 0; rowIndex < row; rowIndex++)
		{
			SDL_Rect slotRect;
			slotRect.w = rect.w;
			slotRect.h = rect.h;
			slotRect.x = rowIndex * rect.w;
			slotRect.y = colIndex * rect.h;
			if (slotRect.x < m_origRect.w && slotRect.y < m_origRect.w)
				this->m_atlasSlot.push_back(slotRect);
		}
	}

	if (this->m_atlasSlot.size() == 0)
		this->DefaultSplite();
}
#pragma endregion






