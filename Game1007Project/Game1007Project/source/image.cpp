#include "image.h"

Image::Image(string filename, int layer)
{
	m_pResource = ResourceManager::GetInstance()->LoadTextureResource(filename);
	m_pCanvas = CanvasManager::GetInstance()->TryGetCanvas(layer);
}

void Image::Update() {}

void Image::Draw() 
{
	DrawingUnit* unit = new DrawingUnit();
	unit->pTranform = this->transform;
	unit->pTexture = this->m_pResource->GetTexture();
	unit->srcRect = this->m_pResource->GetRect();
	m_pCanvas->SetDrawUnit(unit);
}