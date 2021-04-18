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



bool Level::LoadXML(string path)
{
	

	return true;
}
