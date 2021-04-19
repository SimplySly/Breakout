#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(float PosX, float PosY, int Width, int Height, int TextureIndex) 
	: PositionX(PosX), PositionY(PosY), Width(Width), Height(Height), TextureIndex(TextureIndex)
{
}

float Sprite::left()
{
	return PositionX;
}

float Sprite::right()
{
	return PositionX + Width;
}

float Sprite::bottom()
{
	return PositionY + Height;
}

float Sprite::top()
{
	return PositionY;
}

float Sprite::centerX()
{
	return PositionX + Width / 2.0f;
}

float Sprite::centerY()
{
	return PositionY + Height / 2.0f;
}

float Sprite::radius()
{
	return Width / 2.0f;
}
