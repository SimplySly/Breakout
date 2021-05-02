#include "Texture.h"

using namespace std;

void ReleaseTexture(SDL_Texture *pTexture)
{
	SDL_DestroyTexture(pTexture);
	pTexture = nullptr;
}

Texture::Texture()
{
	m_Texture = nullptr;
	m_Width = 0;
	m_Height = 0;
}

Texture::Texture(const Texture& other)
{
	m_Width = other.m_Width;
	m_Height = other.m_Height;
	m_Name = other.m_Name;

	m_Texture = other.m_Texture;
}

Texture::~Texture()
{
	Free();
}

SDL_Texture* Texture::GetTexture() const
{
	return m_Texture.get();
}

const std::string& Texture::GetName() const
{
	return m_Name;
}

int Texture::GetWidth() const
{
	return m_Width;
}

int Texture::GetHeight() const
{
	return m_Height;
}

void Texture::Free()
{
	/*if (m_Texture.unique())
	{
		SDL_DestroyTexture(m_Texture.get());
	}*/
	m_Texture = nullptr;
}

bool Texture::LoadTextureFromFile(const string& path, SDL_Renderer* pRenderer, const string& name)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	m_Width = loadedSurface->w;
	m_Height = loadedSurface->h;
	if (!name.empty())
	{
		m_Name = name;
	}
	else
	{
		m_Name = path;
	}

	//Create texture from surface pixels
	m_Texture.reset(SDL_CreateTextureFromSurface(pRenderer, loadedSurface), ReleaseTexture);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	if (m_Texture == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	return true;
}

bool Texture::CreateFontTexture(const string& text, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor, const string& name)
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, text.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

		return false;
	}
	m_Width = textSurface->w;
	m_Height = textSurface->h;

	if (!name.empty())
	{
		m_Name = name;
	}
	else
	{
		m_Name = text;
	}

	//Create texture from surface pixels
	m_Texture.reset(SDL_CreateTextureFromSurface(pRenderer, textSurface), ReleaseTexture);

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	if (m_Texture == nullptr)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

		return false;
	}

	return true;
}