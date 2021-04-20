#pragma once
#include "Sprite.h"


class Brick
{
public:
	int HitPoints;
	int Score;
	int IsActive;

	void DecreaseHitPoints();

	Sprite sprite;
};
