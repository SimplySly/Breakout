#include "Level.h"
using namespace std;
using namespace tinyxml2;

Level::Level()
{
	m_BackgroundTexture = nullptr;
}
Level::~Level()
{
	if (m_BackgroundTexture)
	{
		delete[] m_BackgroundTexture;
	}
}



bool Level::LoadXML(string path, vector<Brick> &Bricks)
{
	XMLDocument doc;

	doc.LoadFile(path.c_str());

	if (doc.ErrorID())
	{
		return false;
	}

	/*XMLElement* attributeApproachElement = doc.FirstChildElement()->FirstChildElement("attributeApproach");
	attributeApproachElement->QueryStringAttribute("v", &m_BackgroundTexture);*/

	return true;
}
