#include "Input.h"

Input::Input()
{
	for (size_t i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}
}

void Input::KeyDown(unsigned int key)
{
	m_keys[(unsigned short)key] = true;
}

void Input::KeyUp(unsigned int key)
{
	m_keys[(unsigned short)key] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	return m_keys[(unsigned short)key];
}




