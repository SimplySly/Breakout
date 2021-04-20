#include "Brick.h"

void Brick::DecreaseHitPoints()
{
	if (!IsActive || HitPoints == -1)
	{
		return;
	}

	HitPoints--;
	if (HitPoints < 1)
	{
		IsActive = false;
	}
}
