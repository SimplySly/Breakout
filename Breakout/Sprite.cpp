#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(float PosX, float PosY, int Width, int Height, int TextureIndex) 
	: PositionX(PosX), PositionY(PosY), Width(Width), Height(Height), TextureIndex(TextureIndex)
{
}

float Sprite::left() const
{
	return PositionX;
}

float Sprite::right() const
{
	return PositionX + Width;
}

float Sprite::bottom() const
{
	return PositionY + Height;
}

float Sprite::top() const
{
	return PositionY;
}

float Sprite::centerX() const
{
	return PositionX + Width / 2.0f;
}

float Sprite::centerY() const
{
	return PositionY + Height / 2.0f;
}

float Sprite::radius() const
{
	return Width / 2.0f;
}
