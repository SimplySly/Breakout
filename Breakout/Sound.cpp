#include "Sound.h"

void ReleaseSound(Mix_Chunk *pSound)
{
	Mix_FreeChunk(pSound);
	pSound = nullptr;
}


Sound::Sound()
{
}

Sound::Sound(const Sound& other)
{
	m_Sound = other.m_Sound;
}

Sound::~Sound()
{
}

Mix_Chunk* Sound::GetMixChunk() const
{
	return m_Sound.get();
}

bool Sound::LoadSound(const std::string& path)
{
	m_Sound.reset(Mix_LoadWAV(path.c_str()), ReleaseSound);

	if (m_Sound == nullptr)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}
