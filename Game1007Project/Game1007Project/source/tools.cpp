#include "tools.h"
#include "math.h"
#include "game.h"
#include "camera.h"


void GetMovePixel(Vector2* moveVector, int speed, float* x, float* y)
{
	double slide, powX = pow(moveVector->x, 2), powY = pow(moveVector->y, 2), moveX = 0, moveY = 0;
	slide = sqrt(powX + powY);

	if (slide != 0)
	{
		moveX = speed * moveVector->x / slide / 1000 * Game::deltaGameTime;
		moveY = speed * moveVector->y / slide / 1000 * Game::deltaGameTime;
	}

	*x = moveX;
	*y = moveY;
}

void GetMovePixel(Vector2 *moveVector, int speed, int* x, int* y)
{
	double slide, powX = pow(moveVector->x, 2), powY = pow(moveVector->y, 2), moveX = 0, moveY = 0;
	slide = sqrt(powX + powY);

	if (slide != 0) 
	{
		moveX = speed * moveVector->x / slide / 1000 * Game::deltaGameTime;
		moveY = speed * moveVector->y / slide / 1000 * Game::deltaGameTime;
	}

	*x = moveX;
	*y = moveY;
}

void GetCamPosition(std::string camName, Vector2 realPos, Vector2* camPos)
{
	auto cam = CameraManager::GetInstance()->GetCamera(camName);
	GetCamPosition(cam, realPos, camPos);
}

void GetCamPosition(Camera* pCam, Vector2 realPos, Vector2* camPos)
{
	if (pCam != NULL)
	{
		if (camPos == NULL)
			camPos = new Vector2();
		camPos->x = realPos.x - pCam->transform.globalPosition.x;
		camPos->y = realPos.y - pCam->transform.globalPosition.y;
	}
}

void GetRealPosition(std::string camName, Vector2 camPos, Vector2* realPos)
{
	auto cam = CameraManager::GetInstance()->GetCamera(camName);
	GetRealPosition(cam, camPos, realPos);
}

void GetRealPosition(Camera* pCam, Vector2 camPos, Vector2* realPos)
{

	if (pCam != NULL)
	{
		if (realPos == NULL)
			realPos = new Vector2();
		realPos->x = camPos.x + pCam->transform.globalPosition.x;
		realPos->y = camPos.y + pCam->transform.globalPosition.y;
	}
}

