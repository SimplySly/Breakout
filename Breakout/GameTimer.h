#pragma once
#include <SDL.h>

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	void Start();
	unsigned int GetTicks();
	void Pause();
	bool IsPaused();
private:
	int m_CurrentTicks;
	bool m_Paused;
};


