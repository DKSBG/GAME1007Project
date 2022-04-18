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
		Transform camTrs = m_pCamera->transform;
		unit->ScreenPos.x = unit->tranform.globalPosition.x - camTrs.globalPosition.x;
		unit->ScreenPos.y = unit->tranform.globalPosition.y - camTrs.globalPosition.y;
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
	for(int index = 0; index < m_drawUnitList.size(); index++)
	{
		DrawingUnit* unit = m_drawUnitList[index];
		SDL_Rect* dstRect = new SDL_Rect();
		SDL_Texture* pTexture = unit->pTexture;
		dstRect->x = unit->ScreenPos.x;
		dstRect->y = unit->ScreenPos.y;
		dstRect->w = unit->tranform.size.x * unit->tranform.scale.x;
		dstRect->h = unit->tranform.size.y * unit->tranform.scale.y;
		SDL_SetTextureAlphaMod(pTexture, unit->alpha);
		SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), pTexture, &unit->srcRect, dstRect, unit->rotation, NULL, unit->flip);
		delete m_drawUnitList[index];
	}
	m_drawUnitList.clear();
}
#pragma endregion