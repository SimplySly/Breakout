#pragma once
#include "Sprite.h"
#include "Sound.h"
#include "BrickType.h"

class Brick
{
public:
	Brick(const BrickType& brickType, const class Sprite& sprite);

	void DecreaseHitPoints();
	bool IsActive() const;
	int GetScore() const;

	Sprite Sprite;
	Sound HitSound;
	Sound BreakSound;
private:
	int m_HitPoints;
	int m_BreakScore;
	bool m_IsActive;

};
