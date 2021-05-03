#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <memory>

class Sound
{
public:
	Sound();
	Sound(const Sound& other);
	~Sound();

	Mix_Chunk* GetMixChunk() const;

	bool LoadSound(const std::string& path);
private:
	std::shared_ptr<Mix_Chunk> m_Sound;
};

