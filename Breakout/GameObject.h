#pragma once
#include "Sprite.h"
#include "Sound.h"


struct GameObject
{
public:
	GameObject();
	
	float SpeedX;
	float SpeedY;
	
	Sound HitSound;
	Sprite sprite;
};
