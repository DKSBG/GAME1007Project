#pragma once
#include "gameVector.h"
#include <string>
#include "camera.h"

void GetMovePixel(Vector2 *moveVector, int speed, int* x, int* y);
void GetCamPosition(Camera* pCam, Vector2 realPos, Vector2* camPos);
void GetCamPosition(std::string camName, Vector2 realPos, Vector2* camPos);
void GetRealPosition(Camera* pCam, Vector2 camPos, Vector2* realPos);
void GetRealPosition(std::string camName, Vector2 camPos, Vector2* realPos);