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
};

