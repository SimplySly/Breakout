#pragma once
#include "Texture.h"
#include "Brick.h"
#include <vector>

class LevelInfo
{
public:
	LevelInfo();
	
	void SetBackGroundTexture(const Texture &t);
	void AddIndestructibleBrick(const Brick &b);
	void AddDestructibleBrick(const Brick &b);
	void HitBrick(size_t i);
	void Reset();
	bool IsLevelClear();

	SDL_Texture* GetBackgroundTexture();
	const std::vector<Brick>& GetBricks() const;
private:
	Texture m_BackgroundTexture;
	int m_BricksToDestroy;
	std::vector<Brick> m_LevelBricks;
};

