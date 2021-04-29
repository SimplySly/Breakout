#pragma once
#include "Sprite.h"

enum CollisionSide
{
	COLLISION_NONE		= 0,
	COLLISION_LEFT		= 1,
	COLLISION_RIGHT		= 2,
	COLLISION_TOP		= 3,
	COLLISION_BOTTOM	= 4
};

CollisionSide CircleAndRect(const Sprite &circle, const Sprite &rect);

bool CircleContainsDot(const Sprite &circle, float x, float y);
