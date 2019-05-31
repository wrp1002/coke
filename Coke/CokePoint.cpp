#include "CokePoint.h"

CokePoint::CokePoint(int x, int y, int screenWidth, int screenHeight) {
	this->x = x;
	this->y = y;

	this->angle = rand() % 255 * (M_PI / 180);
	this->sizeMult = (3 + rand() % 6) * .1;
	this->dir = atan2((rand() % screenHeight) - y, (rand() % screenWidth) - x);
	this->speed = 7 - sizeMult * 7;

	this->x -= cos(this->dir) * 500;
	this->y -= sin(this->dir) * 500;
	this->lifeState = 0;
	this->rotDir = (rand() % 2 == 0 ? 1 : -1);
}

void CokePoint::Update(int screenWidth, int screenHeight) {
	this->angle += .025 * this->rotDir;
	this->x += cos(this->dir) * this->speed;
	this->y += sin(this->dir) * this->speed;

	if (this->lifeState == 0) {
		if (x > 0 && x < screenWidth && y > 0 && y < screenHeight)
			lifeState = 1;
	}
	else if (lifeState == 1) {
		if (x < -500 || x > screenWidth + 500 || y < -500 || y > screenHeight + 500)
			lifeState = 2;
	}
}
