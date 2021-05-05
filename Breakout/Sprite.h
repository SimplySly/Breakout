#pragma once
#include "Texture.h"

struct Sprite
{
public:
	Sprite();
	Sprite(float posX, float posY, int width, int height, Texture t);

	float PositionX;
	float PositionY;

	int Width;
	int Height;

	SDL_Texture* GetTexture() const;

	float Left() const;
	float Right() const;
	float Bottom() const;
	float Top() const;

	float CenterX() const;
	float CenterY() const;
	float Radius() const;

private:
	Texture m_Texture;
};

