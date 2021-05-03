#pragma once
#include "Sprite.h"
#include "Sound.h"


class GameObject
{
public:
	float SpeedX;
	float SpeedY;

	
	Sound HitSound;
	Sprite sprite;
};
