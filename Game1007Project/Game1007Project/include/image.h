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
class Image : public GOComponent{
public:
	Image(string image, int layer);
	void ChangeSprite(string image);
	void Draw();
	void SetNativeSize();
private:
	TextureResource* m_pResource;
	Canvas* m_pCanvas;
};
