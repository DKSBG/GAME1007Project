#pragma once
#include "gameVector.h"

class Transform {
public:
	Transform();
	~Transform();
	Vector2* position;
	Vector2* size;
	Vector2* scale;
	void Clone(const Transform target);
};