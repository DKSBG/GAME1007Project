#include"SDL.h"
#include"game.h"
#include"resource.h"
#include"canvas.h"

#pragma region CanvasManager Implement
Canvas* CanvasManager::TryGetCanvas(int layer)
{
	auto canvas = m_canvasMap.find(layer);
	Canvas* pCanvas;
	if (canvas == m_canvasMap.end()) 
	{
		pCanvas = new Canvas();
		m_canvasMap.insert(pair<int, Canvas*>(layer, pCanvas));
	}
	else 
	{
		pCanvas = m_canvasMap[layer];
	}
	return pCanvas;
}

void CanvasManager::Draw()
{
	for (auto& Canvas : m_canvasMap)
	{
		Canvas.second->Draw();
	}
}

CanvasManager* CanvasManager::GetInstance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new CanvasManager();
	}

	return s_pInstance;
}
CanvasManager* CanvasManager::s_pInstance = 0;
#pragma endregion

#pragma region Canvas Implement
void Canvas::SetDrawUnit(DrawingUnit* unit)
{
	this->m_drawUnitList.push_back(unit);
}

void Canvas::Draw()
{
	while (m_drawUnitList.size() > 0)
	{
		DrawingUnit* unit = m_drawUnitList.back();
		SDL_Rect* dstRect = new SDL_Rect();
		SDL_Texture* pTexture = unit->pTexture;
		dstRect->x = unit->pTranform->position->x;
		dstRect->y = unit->pTranform->position->y;
		dstRect->w = unit->pTranform->size->x * unit->pTranform->scale->x;
		dstRect->h = unit->pTranform->size->y * unit->pTranform->scale->y;
		SDL_RenderCopy(Game::GetInstance()->GetRenderer(), pTexture, &unit->srcRect, dstRect);
		m_drawUnitList.pop_back();
	}
}
#pragma endregion