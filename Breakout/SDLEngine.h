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
#include "XMLLevelLoader.h"
#include "GameTimer.h"
#include "LevelInfo.h"
#include "Collision.h"
#include "MathExtensions.h"


#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2_image.lib")

//Screen dimension constants
#define SCREEN_WIDTH			800
#define SCREEN_HEIGHT			600

#define HUD_HEIGHT				40

#define PADDLE_SPEED			350.0f
#define BALL_SPEED_X			0.0f
#define BALL_SPEED_Y			400.0f

#define MAX_NORMAL_ROTATION		(PI / 4.0f)


//#define OPPOSITE_DIRECTION_VIA_EDGE
//#define OPPOSITE_DIRECTION_VIA_SPEED

class SDLEngine
{
public:
	SDLEngine();
	SDLEngine(int ScreenWidth, int ScreenHeight);
	~SDLEngine();

	bool Init();
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

	GameTimer m_Timer;

	void RenderSprite(const Sprite* sprite);

	bool BounceOppositeDirection(float distanceX, Vector2 ballDirection);
	bool BallBoundaryUpdate(float ballDeltaX, float ballDeltaY, bool& flipX, bool& flipY);
	void BounceBallOffPaddle();


	int m_ScreenWidth, m_ScreenHeight;
	int m_PlayableScreenWidth, m_PlayableScreenHeight;
	Input *m_Input;

	LevelInfo m_LevelInfo;

	GameObject *m_Paddle, *m_Ball;
	TextureCollection m_Textures;
	std::vector<Brick> m_LevelBricks;
};
