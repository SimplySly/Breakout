#pragma once

#include <SDL.h>

class Input
{
public:
	Input();

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);

	bool IsKeyDown(unsigned int key);
private:
	bool m_keys[SDL_NUM_SCANCODES];
};

