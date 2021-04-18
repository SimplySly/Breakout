#pragma once

#include <SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDLEngine
{
public:
	SDLEngine();
	~SDLEngine();

	bool Init();
	bool LoadMedia();

	void Render();
private:
	//The window we'll be rendering to
	SDL_Window* m_Window;

	//The surface contained by the window
	SDL_Surface* m_ScreenSurface;

	//The image we will load and show on the screen
	SDL_Surface* m_XOut;
};
