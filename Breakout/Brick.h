#pragma once
#include "Sprite.h"


class Brick
{
public:
	int HitPoints;
	int Score;
	int IsActive;
	int HitSoundIndex;
	int BreakSoundIndex;

	void DecreaseHitPoints();

	Sprite sprite;
};
