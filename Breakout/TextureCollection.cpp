#include "TextureCollection.h"

using namespace std;

TextureCollection::TextureCollection()
{
}

TextureCollection::~TextureCollection()
{
	Clear();
}

void TextureCollection::Clear()
{
	for (size_t i = 0; i < m_Textures.size(); i++)
	{
		SDL_DestroyTexture(m_Textures[i]);
	}

	m_Textures.clear();
}

int TextureCollection::Size()
{
	return (int)m_Textures.size();
}

bool TextureCollection::LoadTexture(string path, SDL_Renderer* pRenderer)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	//Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
	if (texture == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	m_Textures.push_back(texture);

	return true;
}
