#include "Input.h"

Input::Input()
{
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_keys[i] = false;
	}

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_keysPress[i] = false;
	}
}

void Input::KeyDown(unsigned int key)
{
	m_keys[(unsigned short)key] = true;
	m_keysPress[(unsigned short)key] = true;
}

void Input::KeyUp(unsigned int key)
{
	m_keys[(unsigned short)key] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	return m_keys[(unsigned short)key];
}

bool Input::IsKeyPressed(unsigned int key)
{
	return m_keysPress[(unsigned short)key];
}

void Input::KeyPressReset()
{
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_keysPress[i] = false;
	}
}




