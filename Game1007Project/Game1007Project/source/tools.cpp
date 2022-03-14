#include "tools.h"
#include "math.h"
#include "game.h"

void GetMovePixel(Vector2 *moveVector, int speed, int* x, int* y)
{
	double slide, powX = pow(moveVector->x, 2), powY = pow(moveVector->y, 2), moveX = 0, moveY = 0;
	slide = sqrt(powX + powY);

	if (slide != 0) 
	{
		moveX = speed * moveVector->x / slide / 1000 * Game::deltaTime;
		moveY = speed * moveVector->y / slide / 1000 * Game::deltaTime;
	}

	*x = moveX;
	*y = moveY;
}