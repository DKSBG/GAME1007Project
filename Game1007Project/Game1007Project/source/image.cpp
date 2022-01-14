#include "image.h"

Image::Image(string filename, int layer)
{
	m_pResource = ResourceManager::GetInstance()->LoadTexture(filename);
	m_pCanvas = CanvasManager::GetInstance()->TryGetCanvas(layer);
}

void Image::Update() {}

void Image::Draw() 
{
	DrawingUnit* unit = new DrawingUnit();
	unit->resource = this->m_pResource;
	unit->tranform = this->transform;
	m_pCanvas->SetDrawUnit(unit);
}