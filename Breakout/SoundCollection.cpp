#include "SoundCollection.h"

using namespace std;

SoundCollection::SoundCollection()
{
}

SoundCollection::~SoundCollection()
{
	Clear();
}

void SoundCollection::Clear()
{
	for (size_t i = 0; i < m_Sounds.size(); i++)
	{
		Mix_FreeChunk(m_Sounds[i]);
		m_Sounds[i] = nullptr;
	}

	m_Sounds.clear();
}

int SoundCollection::Size()
{
	return (int)m_Sounds.size();
}

bool SoundCollection::LoadSound(const string& path)
{
	Mix_Chunk* pSound = Mix_LoadWAV(path.c_str());

	if (pSound == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	m_Sounds.push_back(pSound);

	return true;
}
