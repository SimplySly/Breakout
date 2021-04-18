//Using SDL and standard IO
#include "SDLEngine.h"
#include <iostream>
#include "Main.h"
#define main main   

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

	if (!engine.LoadObjects())
	{
		printf("Failed to load objects!\n");

		return 3;
	}

	engine.Loop();;
	

    return 0;
}