#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	SDL_Texture* pTexture;
	std::string Name;

	int Width;
	int Height;

	void Free();
	bool CreateFontTexture(std::string text, std::string name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);
	bool LoadTextureFromFile(std::string path, std::string name, SDL_Renderer* pRenderer);
};


