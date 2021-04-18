#pragma once
#include "Sprite.h"
#include <tinyxml2.h>
#include <string>
#include <vector>
#include "BrickType.h"
#include "Brick.h"

#pragma comment(lib, "tinyxml2.lib")

class Level
{
public: 
	Level();
	~Level();
	bool LoadXML(std::string path, std::vector<Brick> &bricks);

	int m_RowCount;
	int m_ColumnCount;
	int m_RowSpacing;
	int m_ColumnSpacing;
	char* m_BackgroundTexture;

	std::vector<BrickType> BrickTypes;
};

