#include "Sprite.h"

Sprite::Sprite()
{
	PositionX = 0;
	PositionY = 0;
	Width = 0;
	Height = 0;
}

Sprite::Sprite(float posX, float posY, int width, int height, Texture t) 
	: PositionX(posX), PositionY(posY), Width(width), Height(height), m_Texture(t)
{

}

SDL_Texture* Sprite::GetTexture() const
{
	return m_Texture.GetTexture();
}

float Sprite::Left() const
{
	return PositionX;
}

float Sprite::Right() const
{
	return PositionX + Width;
}

float Sprite::Bottom() const
{
	return PositionY + Height;
}

float Sprite::Top() const
{
	return PositionY;
}

float Sprite::CenterX() const
{
	return PositionX + Width / 2.0f;
}

float Sprite::CenterY() const
{
	return PositionY + Height / 2.0f;
}

float Sprite::Radius() const
{
	return Width / 2.0f;
}
