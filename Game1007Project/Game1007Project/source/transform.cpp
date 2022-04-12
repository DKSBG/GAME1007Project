#include "transform.h"

#pragma region Transform Implement
Transform::Transform()
{
	this->localPosition.Set(0, 0);
	this->globalPosition.Set(0, 0);
	this->scale.Set(1, 1);
	this->size.Set(10, 10);
}

void Transform::Clone(const Transform target)
{
	localPosition.x = target.localPosition.x;
	localPosition.y = target.localPosition.y;
	globalPosition.x = target.globalPosition.x;
	globalPosition.y = target.globalPosition.y;
	size.x = target.size.x;
	size.y = target.size.y;
	scale.x = target.scale.x;
	scale.y = target.scale.y;
}

float Transform::GetHeight()
{
	return size.y * scale.y;
}

float Transform::GetWidth()
{
	return size.x * scale.x;
}

bool Transform::IsLocalPositionModified() 
{
	return (m_lastLocalPosition.x != localPosition.x) || (m_lastLocalPosition.y != localPosition.y);
}

bool Transform::IsGloblePositionModified() 
{
	return (m_lastGlobalPosition.x != globalPosition.x) || (m_lastGlobalPosition.y != globalPosition.y);
}

//bool Transform::IsScaleRateModified(Vector2* rate) 
//{
//	return (m_lastScaleRate.x != rate->x) || (m_lastScaleRate.y != rate->y);
//}

void Transform::ParentUpdatePostion(const Vector2 parentMove)
{
	globalPosition.x += parentMove.x;
	globalPosition.y += parentMove.y;
}

//void Transform::ParentUpdateScale(const Vector2 parentScaleRate) 
//{
//	scale.x *= parentScaleRate.x;
//	scale.y *= parentScaleRate.y;
//}

void Transform::UpdatePostion(Vector2* move) 
{
	if (IsLocalPositionModified()) 
	{
		globalPosition.x += localPosition.x - m_lastLocalPosition.x;
		globalPosition.y += localPosition.y - m_lastLocalPosition.y;
		m_lastLocalPosition.x = localPosition.x;
		m_lastLocalPosition.y = localPosition.y;
	}

	if (IsGloblePositionModified()) 
	{
		move->x = globalPosition.x - m_lastGlobalPosition.x;
		move->y = globalPosition.y - m_lastGlobalPosition.y;
		m_lastGlobalPosition.x = globalPosition.x;
		m_lastGlobalPosition.y = globalPosition.y;
	}
}

//void Transform::UpdateScale(Vector2* scaleRate) 
//{
//	if (IsScaleRateModified(scaleRate))
//	{
//		if()
//		scaleRate->x = scale.x / m_lastScaleRate.x;
//		scaleRate->y = scale.y / m_lastScaleRate.y;
//
//		m_lastScaleRate.x = scale.x;
//		m_lastScaleRate.y = scale.y;
//	}
//}
#pragma endregion