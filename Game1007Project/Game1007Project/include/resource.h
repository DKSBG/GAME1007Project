#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;
#define TEXTUREPATH "assets/texture/"
#define ATLASPATH "assets/atlas/"

//hash<string> pathHash;
typedef void (*TextureResourceDestroy)(int id);

class TextureKindResource
{
public:
	SDL_Texture* GetTexture();
	SDL_Rect GetRect();
protected:
	SDL_Texture* m_pTexture;
	SDL_Rect m_origRect;
};

class TextureResource : public TextureKindResource {
public:
	TextureResource(SDL_Texture* pTexture);
	~TextureResource();
};

class AtlasResource : public TextureKindResource {
public:
	AtlasResource(SDL_Texture* pTexture);
	~AtlasResource();
	void AutoSplite(int row, int col, SDL_Rect rect);
	void AutoSplite(int row, int col);
	void DefaultSplite();
	SDL_Rect GetSlot(int index);
private:
	vector<SDL_Rect> m_atlasSlot;
};

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);
	SDL_Texture* LoadTexture(string filePath, string locatePath);
	TextureResource* LoadTextureResource(string texturePath);
	AtlasResource* LoadAtlasResource(string texturePath);
	//void TextureResourceCollect(int id);
	static ResourceManager* GetInstance();
private:
	map<int, SDL_Texture*> m_textureMap;
	map<int, TextureResource*> m_textureResourceMap;
	map<int, AtlasResource*> m_atlasResourceMap;
	//map<size_t, TextureResource*> m_textureResourceMap;
	SDL_Renderer* m_pRenderer;
	static ResourceManager* s_pInstance;
};



