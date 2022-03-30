#include"SDL.h"
#include"game.h"
#include"resource.h"
#include"canvas.h"
#include"camera.h"

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
	if(m_pCamera != NULL)
	{
		Transform camTrs = m_pCamera->trs;
		unit->tranform.position.x -= camTrs.position.x;
		unit->tranform.position.y -= camTrs.position.y;
		this->m_drawUnitList.push_back(unit);
	}
}

void Canvas::SetCamera(Camera* pCam)
{
	m_pCamera = pCam;

}

Camera* Canvas::GetCamera() 
{
	return m_pCamera;
}

void Canvas::Draw()
{
	while (m_drawUnitList.size() > 0)
	{
		DrawingUnit* unit = m_drawUnitList.back();
		SDL_Rect* dstRect = new SDL_Rect();
		SDL_Texture* pTexture = unit->pTexture;
		dstRect->x = unit->tranform.position.x;
		dstRect->y = unit->tranform.position.y;
		dstRect->w = unit->tranform.size.x * unit->tranform.scale.x;
		dstRect->h = unit->tranform.size.y * unit->tranform.scale.y;
		SDL_RenderCopy(Game::GetInstance()->GetRenderer(), pTexture, &unit->srcRect, dstRect);
		m_drawUnitList.pop_back();
	}
}
#pragma endregion