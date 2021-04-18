#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL_image.h>
#include "Sprite.h"
#include "Input.h"
#include "TextureCollection.h"
#include "Brick.h"
#include "GameObject.h"


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
	void RenderSprite(const Sprite *sprite);
	bool LoadLevelObjects(std::string level);
	void ClearLevelObjects();

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


	int m_ScreenWidth, m_ScreenHeight;
	Input *m_Input;

	GameObject *m_Paddle, *m_Ball;
	TextureCollection m_Textures;
	std::vector<Brick> m_LevelBricks;
};
