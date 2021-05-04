#include "XMLLevelLoader.h"
#include "StdStringExtensions.h"
#include <sstream>
#include "XMLLevelContext.h"

using namespace std;
using namespace tinyxml2;

XMLLevelLoader::XMLLevelLoader()
{
	
}

XMLLevelLoader::~XMLLevelLoader()
{
}

bool XMLLevelLoader::LoadFromXML(const string& path, LevelInfo& levelInfo, SDL_Renderer* pRenderer, int brickAreaWidth, int brickAreaHeight)
{
	XMLDocument doc;
	XMLLevelContext levelContext = { 0 };

	levelContext.BrickSizeX = 9;
	levelContext.BrickSizeY = 3;

	doc.LoadFile(path.c_str());

	if (doc.ErrorID())
	{
		return false;
	}

	XMLElement* levelElement = doc.FirstChildElement("Level");
	if (levelElement == nullptr)
	{
		return false;
	}

	if (!LoadLevelAttributes(levelElement, levelContext))
	{
		return false;
	}

	levelInfo.BackgroundTexture.LoadTextureFromFile(levelContext.BackgroundTexture, pRenderer);

	if (!LoadBrickTypes(levelElement))
	{
		return false;
	}

	if (!LoadBrickTextureAndSounds(pRenderer))
	{
		return false;
	}

	bool ret = LoadBrickList(levelElement, levelContext, levelInfo, brickAreaWidth, brickAreaHeight);
	if (!ret)
	{
		return false;
	}

	return true;
}

bool XMLLevelLoader::LoadBrickTextureAndSounds(SDL_Renderer *pRenderer)
{
	vector<string> loadedSoundNames;
	vector<Sound> brickSounds;

	for (auto& brick : m_BrickTypes)
	{
		if (!brick.Texture.LoadTextureFromFile(brick.TextureName, pRenderer))
		{
			return false;
		}

		if (!LoadBrickSound(brick.HitSound, brick.HitSoundName, loadedSoundNames, brickSounds))
		{
			return false;
		}

		if (brick.BreakSoundName != nullptr)
		{
			if (!LoadBrickSound(brick.BreakSound, brick.BreakSoundName, loadedSoundNames, brickSounds))
			{
				return false;
			}
		}
	}

	return true;
}


bool XMLLevelLoader::LoadBrickSound(Sound& sound, const char* soundName, vector<string>& loadedSoundNames, vector<Sound>& brickSounds)
{
	//recycle for greener planet
	auto it = find(loadedSoundNames.begin(), loadedSoundNames.end(), soundName);
	if (it != loadedSoundNames.end())
	{
		sound = brickSounds[(int)(it - loadedSoundNames.begin())];
	}
	else
	{
		//load new sound...
		Sound s;

		if (!s.LoadSound(soundName))
		{
			return false;
		}

		loadedSoundNames.push_back(soundName);
		brickSounds.push_back(s);

		sound = brickSounds.back();
	}

	return true;
}

bool XMLLevelLoader::LoadLevelAttributes(XMLElement* levelElement, XMLLevelContext& levelContext)
{
	if (levelElement->QueryIntAttribute("RowCount", &levelContext.RowCount) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryIntAttribute("ColumnCount", &levelContext.ColumnCount) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryIntAttribute("RowSpacing", &levelContext.RowSpacing) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryIntAttribute("ColumnSpacing", &levelContext.ColumnSpacing) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryStringAttribute("BackgroundTexture", (const char**)&levelContext.BackgroundTexture) != XML_SUCCESS)
	{
		return false;
	}

	return true;
}

bool XMLLevelLoader::LoadBrickTypes(XMLElement* levelElement)
{
	XMLElement* pBrickTypeList = levelElement->FirstChildElement("BrickTypes");
	if (pBrickTypeList == nullptr)
	{
		return false;
	}

	for (XMLElement* pBrickTypeElement = pBrickTypeList->FirstChildElement("BrickType"); pBrickTypeElement != nullptr; pBrickTypeElement = pBrickTypeElement->NextSiblingElement("BrickType"))
	{
		BrickType brickType;

		if (pBrickTypeElement->QueryStringAttribute("Id", (const char**)&brickType.Id) != XML_SUCCESS)
		{
			return false;
		}
		if (pBrickTypeElement->QueryStringAttribute("Texture", (const char**)&brickType.TextureName) != XML_SUCCESS)
		{
			return false;
		}

		const char* temp;
		if (pBrickTypeElement->QueryStringAttribute("HitPoints", &temp) != XML_SUCCESS)
		{
			return false;
		}

		if (!SDL_strcmp(temp, "Infinite"))
		{
			brickType.HitPoints = -1;
		}
		else
		{
			brickType.HitPoints = SDL_atoi(temp);
		}

		if (pBrickTypeElement->QueryStringAttribute("HitSound", (const char**)&brickType.HitSoundName) != XML_SUCCESS)
		{
			return false;
		}

		if (pBrickTypeElement->QueryStringAttribute("BreakSound", (const char**)&brickType.BreakSoundName) != XML_SUCCESS)
		{
			//can be omitted if brick can't break
			brickType.BreakSoundName = nullptr;
		}

		if (pBrickTypeElement->QueryIntAttribute("BreakScore", &brickType.BreakScore) != XML_SUCCESS)
		{
			//can be omitted if brick can't break
			brickType.BreakScore = 0;
		}

		m_BrickTypes.push_back(brickType);
	}

	return true;
}

bool XMLLevelLoader::LoadBrickList(XMLElement* levelElement, const XMLLevelContext& levelContext, LevelInfo& levelInfo, int brickAreaWidth, int brickAreaHeight)
{
	XMLElement* brickList = levelElement->FirstChildElement("Bricks");
	if (brickList == nullptr)
	{
		return false;
	}
	XMLText* textNode = brickList->FirstChild()->ToText();
	if (textNode == nullptr)
	{
		return false;
	}
	
	float spaceUnitX = (float)brickAreaWidth / (levelContext.ColumnCount * levelContext.BrickSizeX + (levelContext.ColumnCount - 1) * levelContext.ColumnSpacing);
	float spaceUnitY = (float)brickAreaHeight / (levelContext.RowCount * levelContext.BrickSizeY + (levelContext.RowCount - 1) * levelContext.RowSpacing);
	
	const char* brickListString = textNode->Value();

	string s(brickListString);
	trim(s);

	stringstream LevelStream(s);
	string brickId;
	int rowIndex = 0, columnIndex = 0;

	//just to be sure
	levelInfo.BricksToDestroy = 0;

	while (!LevelStream.eof())
	{
		LevelStream >> brickId;

		size_t i;
		for (i = 0; i < m_BrickTypes.size(); i++)
		{
			if (brickId == m_BrickTypes[i].Id)
			{
				Sprite sprite(columnIndex * levelContext.BrickSizeX * spaceUnitX + columnIndex * levelContext.ColumnSpacing * spaceUnitX,
					rowIndex * levelContext.BrickSizeY * spaceUnitY + rowIndex * levelContext.RowSpacing * spaceUnitY,
					(int)(levelContext.BrickSizeX * spaceUnitX),
					(int)(levelContext.BrickSizeY * spaceUnitY),
					m_BrickTypes[i].Texture);
				levelInfo.LevelBricks.push_back(Brick(m_BrickTypes[i], sprite));

				if (m_BrickTypes[i].HitPoints > 0)
				{
					levelInfo.BricksToDestroy++;
				}

				break;
			}
		}

		if (i == m_BrickTypes.size() && brickId != "_")
		{
			return false;
		}

		columnIndex++;
		if (columnIndex >= levelContext.ColumnCount)
		{
			columnIndex = 0;
			rowIndex++;
			if (rowIndex >= levelContext.RowCount)
			{
				//don't read more than specified row count
				return true;
			}
		}

	}

	if (levelInfo.LevelBricks.empty())
	{
		return false;
	}

	return true;
}