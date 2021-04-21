#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include "Texture.h"



class TextureCollection
{

public:
	TextureCollection();
	~TextureCollection();

	inline Texture operator [] (int index)
	{
		return m_Textures[index];
	}

	Texture operator [] (std::string name);

	void Clear();
	int Size();

	bool LoadTexture(std::string path, SDL_Renderer* pRenderer, const char* name = nullptr); 
	bool AddFontTexture(std::string text, std::string name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);
	bool UpdateFontTexture(std::string text, std::string name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);

private:
	std::vector<Texture> m_Textures;
	int GetIndex(std::string name);
};

