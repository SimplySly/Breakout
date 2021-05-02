#pragma once
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	Sprite(float PosX, float PosY, int Width, int Height, Texture t);

	float PositionX;
	float PositionY;

	int Width;
	int Height;

	SDL_Texture* GetTexture();

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

