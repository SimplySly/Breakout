#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <iostream>


class TextureCollection
{

public:
	TextureCollection();
	~TextureCollection();

	inline SDL_Texture* operator [] (int index)
	{
		return m_Textures[index];
	}

	void Clear();
	int Size();

	bool LoadTexture(std::string path, SDL_Renderer* pRenderer);

private:
	std::vector<SDL_Texture*> m_Textures;
};

