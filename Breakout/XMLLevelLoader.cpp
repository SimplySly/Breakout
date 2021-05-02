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

bool XMLLevelLoader::LoadFromXML(const string& path, LevelInfo& levelInfo, vector<Brick>& bricks, SDL_Renderer* pRenderer, SoundCollection &soundCollection, int brickAreaWidth, int brickAreaHeight)
{
	XMLDocument doc;
	XMLLevelContext levelContext = { 0 };
	TextureCollection brickTextures;

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

	int soundBaseIndex = soundCollection.Size();
	vector<string> loadedSounds;

	for (auto& brick : m_BrickTypes)
	{
		if (!brickTextures.LoadTexture(brick.Texture, pRenderer))
		{
			return false;
		}

		auto it = find(loadedSounds.begin(), loadedSounds.end(), brick.HitSound);
		if (it != loadedSounds.end())
		{
			brick.HitSoundIndex = (int)(it - loadedSounds.begin());
		}
		else
		{
			brick.HitSoundIndex = (int)loadedSounds.size();
			loadedSounds.push_back(brick.HitSound);
			if (!soundCollection.LoadSound(brick.HitSound))
			{
				return false;
			}
		}

		if (brick.BreakSound != nullptr)
		{
			it = find(loadedSounds.begin(), loadedSounds.end(), brick.BreakSound);
			if (it != loadedSounds.end())
			{
				brick.BreakSoundIndex = (int)(it - loadedSounds.begin());
			}
			else
			{
				brick.BreakSoundIndex = (int)loadedSounds.size();
				loadedSounds.push_back(brick.BreakSound);
				if (!soundCollection.LoadSound(brick.BreakSound))
				{
					return false;
				}
			}
		}
		else
		{
			//not important but w/e
			brick.BreakSoundIndex = 0;
		}
		
	}

	bool ret = LoadBrickList(levelElement, levelContext, brickTextures, bricks, levelInfo.BricksToDestroy, brickAreaWidth, brickAreaHeight);
	if (!ret)
	{
		return false;
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
		if (pBrickTypeElement->QueryStringAttribute("Texture", (const char**)&brickType.Texture) != XML_SUCCESS)
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

		if (pBrickTypeElement->QueryStringAttribute("HitSound", (const char**)&brickType.HitSound) != XML_SUCCESS)
		{
			return false;
		}

		if (pBrickTypeElement->QueryStringAttribute("BreakSound", (const char**)&brickType.BreakSound) != XML_SUCCESS)
		{
			//can be omitted if brick can't break
			brickType.BreakSound = nullptr;
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

bool XMLLevelLoader::LoadBrickList(XMLElement* levelElement, const XMLLevelContext& levelContext, const TextureCollection& bricksTextures, std::vector<Brick>& bricks, int& BricksToDestroy, int brickAreaWidth, int brickAreaHeight)
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

	BricksToDestroy = 0;

	while (!LevelStream.eof())
	{
		LevelStream >> brickId;

		size_t i;
		for (i = 0; i < m_BrickTypes.size(); i++)
		{
			if (brickId == m_BrickTypes[i].Id)
			{
				Brick brick;

				brick.HitPoints = m_BrickTypes[i].HitPoints;
				brick.Score = m_BrickTypes[i].BreakScore;
				brick.BreakSoundIndex = m_BrickTypes[i].BreakSoundIndex;
				brick.HitSoundIndex = m_BrickTypes[i].HitSoundIndex;
				brick.IsActive = brick.HitPoints > 0 || brick.HitPoints == -1;
				if (brick.HitPoints > 0)
				{
					BricksToDestroy++;
				}

				brick.sprite = Sprite(columnIndex * levelContext.BrickSizeX * spaceUnitX + columnIndex * levelContext.ColumnSpacing * spaceUnitX,
					rowIndex * levelContext.BrickSizeY * spaceUnitY + rowIndex * levelContext.RowSpacing * spaceUnitY,
					(int)(levelContext.BrickSizeX * spaceUnitX),
					(int)(levelContext.BrickSizeY * spaceUnitY),
					bricksTextures[(int)i]);

				bricks.push_back(brick);
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

	if (bricks.empty())
	{
		return false;
	}

	return true;
}