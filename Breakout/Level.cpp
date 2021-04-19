#include "Level.h"
using namespace std;
using namespace tinyxml2;

Level::Level()
{
	m_BackgroundTexture = nullptr;
}
Level::~Level()
{
}



bool Level::LoadXML(string path, int& bgTextureIndex, vector<Brick>& bricks, TextureCollection &textureCollection, SDL_Renderer* pRenderer)
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

	bgTextureIndex = textureCollection.Size();
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

	LoadBrickList(levelElement, textureBaseIndex, bricks);


	return true;
}

bool Level::LoadLevelAttributes(XMLElement *levelElement)
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

bool Level::LoadBrickTypes(XMLElement *levelElement)
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

		if (pBrickTypeElement->QueryStringAttribute("HitPoints", (const char**)&brickType.HitPoints) != XML_SUCCESS)
		{
			return false;
		}

		if (pBrickTypeElement->QueryStringAttribute("HitSound", (const char**)&brickType.HitSound) != XML_SUCCESS)
		{
			return false;
		}

		if (pBrickTypeElement->QueryStringAttribute("BreakSound", (const char**)&brickType.BreakSound) != XML_SUCCESS)
		{
			brickType.BreakSound = nullptr;
		}

		if (pBrickTypeElement->QueryIntAttribute("BreakScore", &brickType.BreakScore) != XML_SUCCESS)
		{
			brickType.BreakScore = 0;
		}

		m_BrickTypes.push_back(brickType);
	}

	return true;
}

bool Level::LoadBrickList(XMLElement* levelElement, int textureBaseIndex, std::vector<Brick> &bricks)
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
	const char* brickListString = textNode->Value();
}