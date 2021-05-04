#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
	SetToDefault();
}

void PlayerInfo::SetToDefault()
{
	m_Lives = DEFAULT_LIFE;
	m_Score = 0;
	m_CurrentLevel = 1;
}

bool PlayerInfo::HasLife() const
{
	return m_Lives > 0;
}

int PlayerInfo::GetNoLives() const
{
	return m_Lives;
}

int PlayerInfo::GetCurrentLevel() const
{
	return m_CurrentLevel;
}

unsigned int PlayerInfo::GetScore() const
{
	return m_Score;
}

void PlayerInfo::LoseLife()
{
	if (m_Lives > 0)
	{
		m_Lives--;
	}
}

void PlayerInfo::LevelCompleted()
{
	m_CurrentLevel++;
}

void PlayerInfo::AddScore(unsigned int score)
{
	m_Score += score;
}
