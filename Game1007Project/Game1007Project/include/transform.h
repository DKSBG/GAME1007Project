#pragma once
#include "gameVector.h"

class Transform {
public:
	Transform();
	Vector2 localPosition;
	Vector2 globalPosition;
	Vector2 size;
	Vector2 scale;
	double rotation;
	bool IsLocalPositionModified();
	bool IsGloblePositionModified();
	//bool IsScaleRateModified(Vector2* rate);
	void ParentUpdatePostion(const Vector2 parentMove);
	//void ParentUpdateScale(const Vector2 parentScaleRate);
	void UpdatePostion(Vector2* pMove);
	//void UpdateScale(Vector2* pScaleRate);
	float GetHeight();
	float GetWidth();
	void Clone(const Transform target);
private:
	Vector2 m_lastLocalPosition;
	Vector2 m_lastGlobalPosition;
	//Vector2 m_lastScaleRate;
};