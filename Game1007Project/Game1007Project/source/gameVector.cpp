#include"gameVector.h"

Vector2::Vector2() 
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y) 
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2() {}

Vector2 Vector2::operator+(const Vector2& obj)
{
	Vector2 vector2;
	vector2.x = this->x + obj.x;
	vector2.x = this->y + obj.y;
	return vector2;
}

Vector2 Vector2::operator* (const int& obj)
{
	Vector2 vector2;
	vector2.x = this->x * obj;
	vector2.x = this->y * obj;
	return vector2;
}

void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2::Set(const Vector2 v)
{
	this->x = v.x;
	this->y = v.y;
}