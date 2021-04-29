#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
public:
	Texture();
	Texture(const Texture &other);
	~Texture();

	SDL_Texture* pTexture;
	std::string Name;

	int GetWidth() const;
	int GetHeight() const;

	void Free();
	bool CreateFontTexture(const std::string& text, const std::string& name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);
	bool LoadTextureFromFile(const std::string& path, const std::string& name, SDL_Renderer* pRenderer);

private:
	int Width;
	int Height;
};


