#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>

class Texture
{
public:
	Texture();
	Texture(const Texture &other);
	~Texture();
	
	SDL_Texture* GetTexture() const;
	const std::string& GetName() const;

	int GetWidth() const;
	int GetHeight() const;

	void Free();
	bool CreateFontTexture(const std::string& text, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor, const std::string& name = std::string());
	bool LoadTextureFromFile(const std::string& path, SDL_Renderer* pRenderer, const std::string& name = std::string());

private:
	int m_Width;
	int m_Height;

	std::shared_ptr<SDL_Texture> m_Texture;
	std::string m_Name;
};


