#pragma once
#include "Sprite.h"
#include "Sound.h"

class Brick
{
public:
	int HitPoints;
	int Score;
	bool IsActive;

	void DecreaseHitPoints();

	Sprite sprite;
	Sound HitSound;
	Sound BreakSound;
};
