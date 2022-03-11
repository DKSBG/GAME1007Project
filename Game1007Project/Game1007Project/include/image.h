#pragma once
#include <iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"gameVector.h"
#include"gameObject.h"
#include"canvas.h"
#include"resource.h"
#include <map>

using namespace std;
/*
class ImageResource
{
public:
	bool LoadImage(string id);
	bool GetImage(string id);
private:
	map<string, SDL_Texture*> m_imageMap;
};
*/

class Image : public GOComponent{
public:
	Image(string image, int layer);
	void Draw();
	void SetNativeSize();
private:
	TextureResource* m_pResource;
	Canvas* m_pCanvas;
};
