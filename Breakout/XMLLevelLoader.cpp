#include "XMLLevelLoader.h"
#include "StdStringExtensions.h"
#include <sstream>

using namespace std;
using namespace tinyxml2;

XMLLevelLoader::XMLLevelLoader()
{
	m_BackgroundTexture = nullptr;

	m_BrickSizeX = 9;
	m_BrickSizeY = 3;
}

XMLLevelLoader::~XMLLevelLoader()
{
}

bool XMLLevelLoader::LoadFromXML(string path, LevelInfo& levelInfo, vector<Brick>& bricks, TextureCollection& textureCollection, SDL_Renderer* pRenderer, int brickAreaWidth, int brickAreaHeight)
{
	XMLDocument doc;

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

	if (!LoadLevelAttributes(levelElement))
	{
		return false;
	}

	levelInfo.BackgroundTextureIndex = textureCollection.Size();
	if (!textureCollection.LoadTexture(m_BackgroundTexture, pRenderer))
	{
		return false;
	}

	if (!LoadBrickTypes(levelElement))
	{
		return false;
	}

	int textureBaseIndex = textureCollection.Size();
	for (const auto& brick : m_BrickTypes)
	{
		if (!textureCollection.LoadTexture(brick.Texture, pRenderer))
		{
			return false;
		}
	}

	bool ret = LoadBrickList(levelElement, textureBaseIndex, bricks, levelInfo.BricksToDestroy, brickAreaWidth, brickAreaHeight);
	if (!ret)
	{
		return false;
	}

	return true;
}

bool XMLLevelLoader::LoadLevelAttributes(XMLElement* levelElement)
{
	if (levelElement->QueryIntAttribute("RowCount", &m_RowCount) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryIntAttribute("ColumnCount", &m_ColumnCount) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryIntAttribute("RowSpacing", &m_RowSpacing) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryIntAttribute("ColumnSpacing", &m_ColumnSpacing) != XML_SUCCESS)
	{
		return false;
	}
	if (levelElement->QueryStringAttribute("BackgroundTexture", (const char**)&m_BackgroundTexture) != XML_SUCCESS)
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

bool XMLLevelLoader::LoadBrickList(XMLElement* levelElement, int textureBaseIndex, std::vector<Brick>& bricks, int& BricksToDestroy, int brickAreaWidth, int brickAreaHeight)
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
	
	float spaceUnitX = (float)brickAreaWidth / (m_ColumnCount * m_BrickSizeX + (m_ColumnCount - 1) * m_ColumnSpacing);
	float spaceUnitY = (float)brickAreaHeight / (m_RowCount * m_BrickSizeY + (m_RowCount - 1) * m_RowSpacing);
	
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

		for (size_t i = 0; i < m_BrickTypes.size(); i++)
		{
			if (brickId == m_BrickTypes[i].Id)
			{
				Brick brick;

				brick.HitPoints = m_BrickTypes[i].HitPoints;
				brick.Score = m_BrickTypes[i].BreakScore;
				brick.IsActive = brick.HitPoints > 0 || brick.HitPoints == -1;
				if (brick.HitPoints > 0)
				{
					BricksToDestroy++;
				}

				brick.sprite = Sprite(columnIndex * m_BrickSizeX * spaceUnitX + columnIndex * m_ColumnSpacing * spaceUnitX,
					rowIndex * m_BrickSizeY * spaceUnitY + rowIndex * m_RowSpacing * spaceUnitY,
					m_BrickSizeX * spaceUnitX,
					m_BrickSizeY * spaceUnitY,
					textureBaseIndex + i);

				bricks.push_back(brick);

				columnIndex++;
				if (columnIndex >= m_ColumnCount)
				{
					columnIndex = 0;
					rowIndex++;
					if (rowIndex >= m_RowCount)
					{
						//don't read more than specified row count
						return true;
					}
				}

				break;
			}
		}
	}

	if (bricks.empty())
	{
		return false;
	}

	return true;
}