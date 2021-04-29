#include "Texture.h"

using namespace std;

Texture::Texture()
{
	pTexture = nullptr;
	Width = 0;
	Height = 0;
}

Texture::Texture(const Texture& other)
{
	Width = other.Width;
	Height = other.Height;
	Name = other.Name;
	pTexture = other.pTexture;
}

Texture::~Texture()
{

}

int Texture::GetWidth() const
{
	return Width;
}

int Texture::GetHeight() const
{
	return Height;
}

void Texture::Free()
{
	SDL_DestroyTexture(pTexture);
	pTexture = nullptr;
}

bool Texture::LoadTextureFromFile(const string& path, const string& name, SDL_Renderer* pRenderer)
{
	//Free if something existed
	Free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	Width = loadedSurface->w;
	Height = loadedSurface->h;
	Name = name;

	//Create texture from surface pixels
	pTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	if (pTexture == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	return true;
}

bool Texture::CreateFontTexture(const string& text, const string& name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor)
{
	//Free if something existed
	Free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, text.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

		return false;
	}
	Width = textSurface->w;
	Height = textSurface->h;
	Name = name;

	//Create texture from surface pixels
	pTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	if (pTexture == nullptr)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

		return false;
	}

	return true;
}