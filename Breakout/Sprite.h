#pragma once
class Sprite
{
public:
	Sprite();
	Sprite(int PosX, int PosY, int Width, int Height, int TextureIndex);

	float PositionX;
	float PositionY;

	int Width;
	int Height;

	int TextureIndex;
};

