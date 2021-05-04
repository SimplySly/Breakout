#pragma once
#include "Sound.h"
#include "Texture.h"

struct BrickType
{
public:
    char* Id;
    char* TextureName;
    Texture Texture;
    int HitPoints;
    char* HitSoundName;
    Sound HitSound;
    char* BreakSoundName;
    Sound BreakSound;
    unsigned int BreakScore;
};

