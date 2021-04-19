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

	bgTextureIndex = textureCollection.Size();
	if (!textureCollection.LoadTexture(m_BackgroundTexture, pRenderer))
	{
		return false;
	}

	return true;
}
