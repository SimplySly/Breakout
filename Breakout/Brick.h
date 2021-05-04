#pragma once
#include "Sprite.h"
#include "Sound.h"
#include "BrickType.h"
#include <SDL_Image.h>

class Brick
{
public:
	Brick(const BrickType& brickType, const class Sprite& sprite);

	void DecreaseHitPoints();
	bool IsActive() const;
	unsigned int GetScore() const;

	const Sprite& GetSprite() const;

	//without const cuz of SDL library
	Mix_Chunk* GetHitSound() const;
	Mix_Chunk* GetBreakSound() const;
private:
	int m_HitPoints;
	unsigned int m_BreakScore;
	bool m_IsActive;

	Sprite m_Sprite;
	Sound m_HitSound;
	Sound m_BreakSound;

};
