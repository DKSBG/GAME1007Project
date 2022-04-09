#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

using namespace std;
#define TEXTUREPATH "assets/texture/"
#define ATLASPATH "assets/atlas/"
#define SOUNDPATH "assets/sound/"
#define MUSICPATH "assets/music/"

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

class SoundResource {
public:
	SoundResource(Mix_Chunk* pSoundChunk);
	~SoundResource();
	Mix_Chunk* GetSoundChunk();
private:
	Mix_Chunk* m_pSoundChunk;
};

class MusicResource {
public:
	MusicResource(Mix_Music* pMusic);
	~MusicResource();
	Mix_Music* GetMusic(); 
private:
	Mix_Music* m_pMusic;
};

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);
	SDL_Texture* LoadTexture(string filePath, string locatePath);
	TextureResource* LoadTextureResource(string texturePath);
	AtlasResource* LoadAtlasResource(string texturePath);
	SoundResource* LoadSoundResource(string soundPath);
	MusicResource* LoadMusicResource(string musicPath);
	//void TextureResourceCollect(int id);
	static ResourceManager* GetInstance();
private:
	map<int, SDL_Texture*> m_textureMap;
	map<int, TextureResource*> m_textureResourceMap;
	map<int, AtlasResource*> m_atlasResourceMap;
	map<int, SoundResource*> m_soundResoureMap;
	map<int, MusicResource*> m_musicResoureMap;
	//map<size_t, TextureResource*> m_textureResourceMap;
	SDL_Renderer* m_pRenderer;
	static ResourceManager* s_pInstance;
};



