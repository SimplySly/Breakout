
#include "Main.h"   

int main(int argc, char* args[])
{
    SDLEngine engine;

	if (!engine.Init())
	{
		printf("Failed to initialize!\n");

		return 1;
	}

	engine.Loop();
	

    return 0;
}

