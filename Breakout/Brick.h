#pragma once
#include "Sprite.h"


class Brick
{
public:
	int HitPoints;
	int Score;
	bool IsActive;
	int HitSoundIndex;
	int BreakSoundIndex;

	void DecreaseHitPoints();

	Sprite sprite;
};
