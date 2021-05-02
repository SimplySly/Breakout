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

	inline Texture operator [] (int index) const
	{
		return m_Textures[index];
	}

	Texture operator [] (const std::string& name) const;

	void Clear();
	int Size() const;

	bool LoadTexture(const std::string& path, SDL_Renderer* pRenderer, const char* name = nullptr);
	bool AddFontTexture(const std::string& text, const std::string& name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);
	bool UpdateFontTexture(const std::string& text, const std::string& name, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);

private:
	std::vector<Texture> m_Textures;
	int GetIndex(const std::string& name) const;
};

