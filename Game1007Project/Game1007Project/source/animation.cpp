#include"animation.h"
#include"resource.h"
#include"canvas.h"
#include"game.h"

Animation::Animation(string atlasName, int layer, int startIdx, int endIdx, int interval) 
{
	m_pResource = ResourceManager::GetInstance()->LoadAtlasResource(atlasName);
	m_pCanvas = CanvasManager::GetInstance()->TryGetCanvas(layer);
	m_startIdx = startIdx;
	m_endIdx = endIdx;
	m_interval = interval;
	m_currentIdx = m_startIdx;
}

void Animation::Update()
{
	m_deltaTime += Game::GetInstance()->deltaTime;
	if (m_deltaTime > m_interval) 
	{
		m_currentIdx++;
		if (m_currentIdx > m_endIdx)
			m_currentIdx = m_startIdx;
		m_deltaTime = 0;
	}
}

void Animation::Draw()
{
	DrawingUnit* unit = new DrawingUnit();
	unit->pTranform = this->transform;
	unit->pTexture = this->m_pResource->GetTexture();
	unit->srcRect = this->m_pResource->GetSlot(m_currentIdx);
	m_pCanvas->SetDrawUnit(unit);

}