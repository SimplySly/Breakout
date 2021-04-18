#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(int PosX, int PosY, int Width, int Height, int TextureIndex) 
	: PositionX(PosX), PositionY(PosY), Width(Width), Height(Height), TextureIndex(TextureIndex)
{
}
