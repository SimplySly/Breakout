#include "Brick.h"


Brick::Brick(const BrickType& brickType, const class Sprite& sprite) 
{
	m_HitPoints = brickType.HitPoints;
	m_BreakScore = brickType.BreakScore;
	BreakSound = brickType.BreakSound;
	HitSound = brickType.HitSound;


	Sprite = sprite;

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

int Brick::GetScore() const
{
	return m_BreakScore;
}
