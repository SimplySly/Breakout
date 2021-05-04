#pragma once
#include "Texture.h"
#include "Brick.h"
#include <vector>

class LevelInfo
{
public:
	LevelInfo();

	Texture BackgroundTexture;
	int BricksToDestroy;
	std::vector<Brick> LevelBricks;
};

