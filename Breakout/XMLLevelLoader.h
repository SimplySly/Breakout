#pragma once
#include "Sprite.h"
#include <tinyxml2.h>
#include <string>
#include <vector>
#include <SDL.h>
#include "BrickType.h"
#include "Brick.h"
#include "TextureCollection.h"
#include "LevelInfo.h"
#include "SoundCollection.h"

#pragma comment(lib, "tinyxml2.lib")

class XMLLevelLoader
{
public: 
	XMLLevelLoader();
	~XMLLevelLoader();
	bool LoadFromXML(const std::string& path, LevelInfo &levelInfo, std::vector<Brick>& bricks, TextureCollection& textureCollection, SDL_Renderer* pRenderer, SoundCollection& soundCollection, int brickAreaWidth, int brickAreaHeight);


private:
	bool LoadBrickTypes(tinyxml2::XMLElement* levelElement);
	bool LoadLevelAttributes(tinyxml2::XMLElement* levelElement);
	bool LoadBrickList(tinyxml2::XMLElement* levelElement, int textureBaseIndex, std::vector<Brick> &bricks, int &BricksToDestroy, int brickAreaWidth, int brickAreaHeight);

	int m_RowCount;
	int m_ColumnCount;
	int m_RowSpacing;
	int m_ColumnSpacing;
	char* m_BackgroundTexture;


	int m_BrickSizeX;
	int m_BrickSizeY;


	std::vector<BrickType> m_BrickTypes;
};

