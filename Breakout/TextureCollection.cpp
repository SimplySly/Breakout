#include "TextureCollection.h"

using namespace std;

TextureCollection::TextureCollection()
{
}

TextureCollection::~TextureCollection()
{
	Clear();
}

int TextureCollection::GetIndex(const string& name)
{
	auto it = find_if(m_Textures.begin(), m_Textures.end(), [name](const Texture& v) {return v.Name == name; });
	if (it != m_Textures.end())
	{
		return (int)(it - m_Textures.begin());
	}

	return -1;
}

Texture TextureCollection::operator [] (const string& name)
{
	int index = GetIndex(name);
	if (index != -1)
	{
		return m_Textures[index];
	}

	return Texture();
}


void TextureCollection::Clear()
{
	for (auto &x : m_Textures)
	{
		x.Free();
	}
	m_Textures.clear();
}

int TextureCollection::Size()
{
	return (int)m_Textures.size();
}

bool TextureCollection::LoadTexture(const string& path, SDL_Renderer* pRenderer, const char* name)
{
	Texture texture;


	if (name == nullptr)
	{
		if (!texture.LoadTextureFromFile(path, path, pRenderer))
		{
			return false;
		}
	}
	else
	{
		if (!texture.LoadTextureFromFile(path, name, pRenderer))
		{
			return false;
		}
	}

	m_Textures.push_back(texture);

	return true;
}


bool TextureCollection::AddFontTexture(const string& text, const string& name, SDL_Renderer* pRenderer, TTF_Font *pFont, SDL_Color textColor)
{
	Texture texture;
	
	if (!texture.CreateFontTexture(text, name, pRenderer, pFont, textColor))
	{
		return false;
	}

	m_Textures.push_back(texture);

	return true;
}

bool TextureCollection::UpdateFontTexture(const string& text, const string& name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor)
{
	int index = GetIndex(name);

	if (index == -1)
	{
		return false;
	}

	if (!m_Textures[index].CreateFontTexture(text, name, pRenderer, pFont, textColor))
	{
		return false;
	}

	return true;
}
