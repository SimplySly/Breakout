#pragma once
#define DEFAULT_LIFE 3

class PlayerInfo
{
public:
	PlayerInfo();

	int Life;
	int CurrentLevel;
	int Score;

	void SetToDefault();
};

