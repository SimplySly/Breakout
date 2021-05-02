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
#include "XMLLevelContext.h"

#pragma comment(lib, "tinyxml2.lib")

class XMLLevelLoader
{
public: 
	XMLLevelLoader();
	~XMLLevelLoader();
	bool LoadFromXML(const std::string& path, LevelInfo &levelInfo, std::vector<Brick>& bricks, SDL_Renderer* pRenderer, SoundCollection& soundCollection, int brickAreaWidth, int brickAreaHeight);


private:
	bool LoadLevelAttributes(tinyxml2::XMLElement* levelElement, XMLLevelContext& levelContext);
	bool LoadBrickTypes(tinyxml2::XMLElement* levelElement);
	bool LoadBrickList(tinyxml2::XMLElement* levelElement, const XMLLevelContext& levelContext, const TextureCollection &textures, std::vector<Brick> &bricks, int &BricksToDestroy, int brickAreaWidth, int brickAreaHeight);

	std::vector<BrickType> m_BrickTypes;
};

