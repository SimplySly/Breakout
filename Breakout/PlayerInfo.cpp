#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
	SetToDefault();
}

void PlayerInfo::SetToDefault()
{
	Life = DEFAULT_LIFE;
	Score = 0;
	CurrentLevel = 1;
}
