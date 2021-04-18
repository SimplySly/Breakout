#include "SDLEngine.h"

SDLEngine::SDLEngine()
{
	m_Window = nullptr;
	m_ScreenSurface = nullptr;
	m_XOut = nullptr;
}

SDLEngine::~SDLEngine()
{
	//Deallocate surface
	SDL_FreeSurface(m_XOut);
	m_XOut = NULL;

	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool SDLEngine::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			m_ScreenSurface = SDL_GetWindowSurface(m_Window);
		}
	}

	return success;
}

bool SDLEngine::LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	m_XOut = SDL_LoadBMP("x.bmp");
	if (m_XOut == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void SDLEngine::Render()
{
	//Apply the image
	SDL_BlitSurface(m_XOut, NULL, m_ScreenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(m_Window);
}
