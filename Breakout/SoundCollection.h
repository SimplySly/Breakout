#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <iostream>

class SoundCollection
{
public:
	SoundCollection();
	~SoundCollection();

	inline Mix_Chunk* operator [] (int index)
	{
		return m_Sounds[index];
	}

	void Clear();
	int Size();

	bool LoadSound(std::string path);

private:
	std::vector<Mix_Chunk*> m_Sounds;
};


