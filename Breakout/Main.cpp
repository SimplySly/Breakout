//Using SDL and standard IO
#include "SDLEngine.h"
#include <iostream>
#define main main   
#pragma comment (lib, "SDL2.lib")



int main(int argc, char* args[])
{
    SDLEngine engine;

	if (!engine.Init())
	{
		printf("Failed to initialize!\n");

		return 1;
	}

	if (!engine.LoadMedia())
	{
		printf("Failed to load media!\n");

		return 2;
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		engine.Render();
	}
	

    return 0;
}