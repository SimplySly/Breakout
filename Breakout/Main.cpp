//Using SDL and standard IO

#include "Main.h"   

int main(int argc, char* args[])
{
    SDLEngine engine;

	if (!engine.Init())
	{
		printf("Failed to initialize!\n");

		return 1;
	}

	if (!engine.LoadLevelObjects("Levels/Level1.xml"))
	{
		printf("Failed to load objects!\n");

		return 2;
	}

	engine.Loop();
	

    return 0;
}