#pragma once
class Sprite
{
public:
	Sprite();
	Sprite(float PosX, float PosY, int Width, int Height, int TextureIndex);

	float PositionX;
	float PositionY;

	int Width;
	int Height;

	int TextureIndex;

	float left() const;
	float right() const;
	float bottom() const;
	float top() const;

	float centerX() const;
	float centerY() const;
	float radius() const;
};

