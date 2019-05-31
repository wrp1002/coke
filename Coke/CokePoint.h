#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>

class CokePoint
{
public:
	int x, y, rotDir;
	double angle, sizeMult, dir, speed;
	int lifeState;
	CokePoint(int x, int y, int screenWidth, int screenHeight);

	void Update(int screenWidth, int screenHeight);
};

