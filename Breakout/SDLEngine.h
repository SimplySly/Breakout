#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "Sprite.h"
#include "Input.h"


#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2_image.lib")

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDLEngine
{
public:
	SDLEngine();
	SDLEngine(int ScreenWidth, int ScreenHeight);
	~SDLEngine();

	bool Init();
	bool LoadMedia();
	void RenderSprite(Sprite *sprite);
	SDL_Texture* LoadTexture(std::string path);
	bool LoadObjects();

	void Loop();
	void Update();
	void Render();
private:
	//The window we'll be rendering to
	SDL_Window* m_Window;

	//The surface contained by the window
	SDL_Surface* m_ScreenSurface;

	//The window renderer
	SDL_Renderer* m_Renderer;

	//Current displayed texture
	SDL_Texture* m_Texture;

	int m_ScreenWidth, m_ScreenHeight;
	Input *m_Input;

	Sprite *m_paddle;
};
