#include "Brick.h"


Brick::Brick(const BrickType& brickType, const Sprite& sprite) 
{
	m_HitPoints = brickType.HitPoints;
	m_BreakScore = brickType.BreakScore;
	m_BreakSound = brickType.BreakSound;
	m_HitSound = brickType.HitSound;


	m_Sprite = sprite;

	m_IsActive = true;
}

void Brick::DecreaseHitPoints()
{
	if (!m_IsActive || m_HitPoints == -1)
	{
		return;
	}

	m_HitPoints--;
	if (m_HitPoints < 1)
	{
		m_IsActive = false;
	}
}

bool Brick::IsActive() const
{
	return m_IsActive;
}

unsigned int Brick::GetScore() const
{
	return m_BreakScore;
}

const Sprite& Brick::GetSprite() const
{
	return m_Sprite;
}

Mix_Chunk* Brick::GetHitSound() const
{
	return m_HitSound.GetMixChunk();
}

Mix_Chunk* Brick::GetBreakSound() const
{
	return m_BreakSound.GetMixChunk();
}
