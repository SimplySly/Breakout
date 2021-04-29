#include "GameTimer.h"


GameTimer::GameTimer()
{
	m_CurrentTicks = 0;
	m_Paused = true;
}

GameTimer::~GameTimer()
{
}

void GameTimer::Start()
{
	m_CurrentTicks = SDL_GetTicks();
	m_Paused = false;
}

unsigned int GameTimer::GetTicks()
{
	unsigned int TimeDelta = 0;

	if (!m_Paused)
	{
		TimeDelta = SDL_GetTicks() - m_CurrentTicks;
		m_CurrentTicks = SDL_GetTicks();
	}

	return TimeDelta;
}

void GameTimer::Pause()
{
	m_Paused = true;
}

bool GameTimer::IsPaused() const
{
	return m_Paused;
}
