#include "image.h"

Image::Image(string filename, int layer)
{
	m_pResource = ResourceManager::GetInstance()->LoadTextureResource(filename);
	m_pCanvas = CanvasManager::GetInstance()->TryGetCanvas(layer);
}

void Image::ChangeSprite(string filename) 
{
	m_pResource = ResourceManager::GetInstance()->LoadTextureResource(filename);
}


void Image::Draw()
{
	DrawingUnit* unit = new DrawingUnit();
	unit->tranform.Clone(*this->transform);
	unit->pTexture = this->m_pResource->GetTexture();
	unit->srcRect = this->m_pResource->GetRect();
	m_pCanvas->SetDrawUnit(unit);
}

Canvas* Image::GetCanvas() 
{
	return m_pCanvas;
}

void Image::SetNativeSize() 
{
	transform->size = new Vector2(m_pResource->GetRect().w, m_pResource->GetRect().h);
}