#include "LevelInfo.h"

LevelInfo::LevelInfo()
{
	m_BricksToDestroy = 0;
}

void LevelInfo::SetBackGroundTexture(const Texture& t)
{
	m_BackgroundTexture = t;
}

void LevelInfo::AddIndestructibleBrick(const Brick& b)
{
	m_LevelBricks.push_back(b);
}

void LevelInfo::AddDestructibleBrick(const Brick& b)
{
	m_BricksToDestroy++;
	m_LevelBricks.push_back(b);
}

void LevelInfo::HitBrick(size_t i)
{
	if (i < m_LevelBricks.size())
	{
		m_LevelBricks[i].DecreaseHitPoints();

		if (!m_LevelBricks[i].IsActive())
		{
			m_BricksToDestroy--;
		}
	}
}

void LevelInfo::Reset()
{
	m_BackgroundTexture.Free();
	m_LevelBricks.clear();
	m_BricksToDestroy = 0;
}

bool LevelInfo::IsLevelClear()
{
	return m_BricksToDestroy < 1;
}

SDL_Texture* LevelInfo::GetBackgroundTexture()
{
	return m_BackgroundTexture.GetTexture();
}

const std::vector<Brick>& LevelInfo::GetBricks() const
{
	return m_LevelBricks;
}
