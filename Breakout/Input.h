#pragma once

#include <SDL.h>

class Input
{
public:
	Input();

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);

	bool IsKeyDown(unsigned int key) const;
	bool IsKeyPressed(unsigned int key) const;
	void KeyPressReset();
private:
	bool m_keys[SDL_NUM_SCANCODES];
	bool m_keysPress[SDL_NUM_SCANCODES];
};

