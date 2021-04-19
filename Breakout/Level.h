#pragma once
#include "Sprite.h"
#include <tinyxml2.h>
#include <string>
#include <vector>
#include <SDL.h>
#include "BrickType.h"
#include "Brick.h"
#include "TextureCollection.h"

#pragma comment(lib, "tinyxml2.lib")

class Level
{
public: 
	Level();
	~Level();
	bool LoadXML(std::string path, int& bgTextureIndex, std::vector<Brick>& bricks, TextureCollection& textureCollection, SDL_Renderer* pRenderer);

	int m_RowCount;
	int m_ColumnCount;
	int m_RowSpacing;
	int m_ColumnSpacing;
	char* m_BackgroundTexture;

	std::vector<BrickType> BrickTypes;
};

