#pragma once
#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
#define TEXTUREPATH "assets/texture/"

//hash<string> pathHash;
typedef void (*TextureResourceDestroy)(int id);

class TextureResource {
public:
	TextureResource(SDL_Texture* pTexture);
	~TextureResource();
	SDL_Texture* pTexture;
	// TODO: Some mistake here.
	//TextureResourceDestroy DestroyCallback;
};

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);
	TextureResource* LoadTexture(string texturePath);
	//void TextureResourceCollect(int id);
	static ResourceManager* GetInstance();
private:
	map<string, TextureResource*> m_textureResourceMap;
	//map<size_t, TextureResource*> m_textureResourceMap;
	SDL_Renderer* m_pRenderer;
	static ResourceManager* s_pInstance;
};



