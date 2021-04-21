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
#include "PlayerInfo.h"


#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2_image.lib")

//Screen dimension constants
#define SCREEN_WIDTH			800
#define SCREEN_HEIGHT			600

#define HUD_HEIGHT				40

#define PADDLE_SPEED			350.0f
#define PADDLE_WIDTH			100
#define PADDLE_HEIGHT			20

#define BALL_RADIUS				20
#define BALL_SPEED_X			0.0f
#define BALL_SPEED_Y			400.0f

#define MAX_NORMAL_ROTATION		(PI / 4.0f)


//#define OPPOSITE_DIRECTION_VIA_EDGE
//#define OPPOSITE_DIRECTION_VIA_SPEED

enum GAME_STATE {
	GAME_STATE_LEVEL_DISPLAY = 0,
	GAME_STATE_PAUSE,
	GAME_STATE_PLAYING,
	GAME_STATE_LOSE,
	GAME_STATE_WIN,
	GAME_STATE_QUIT
};

#define LEVEL_DISPLAY_TEXTURE	"Textures/state/LevelDisplay.jpg"
#define WIN_TEXTURE		"Textures/state/win.jpg"
#define LOSE_TEXTURE		"Textures/state/lose.jpg"

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

	SDL_Texture* m_WinTexture;
	SDL_Texture* m_LoseTexture;
	SDL_Texture* m_LevelDisplayTexture;

	GameTimer m_Timer;

	bool InitGameState(); 
	bool LoadLevelList();
	SDL_Texture* LoadTexture(std::string path);

	void RenderSprite(const Sprite* sprite);

	bool BounceOppositeDirection(float distanceX, Vector2 ballDirection);
	bool BallBoundaryUpdate(float ballDeltaX, float ballDeltaY, bool& flipX, bool& flipY);
	void BounceBallOffPaddle();
	void UpdatePlayingState();

	void ResetGameObjects();
	void BallDeath();
	void LevelWin();

	void RenderGame();
	void RenderTexture(SDL_Texture* pTexture);

	int m_ScreenWidth, m_ScreenHeight;
	int m_PlayableScreenWidth, m_PlayableScreenHeight;
	Input *m_Input;

	LevelInfo m_LevelInfo;
	PlayerInfo m_PlayerInfo;
	GAME_STATE m_GameState;
	std::vector<std::string> m_LevelList;

	GameObject *m_Paddle, *m_Ball;
	TextureCollection m_Textures;
	std::vector<Brick> m_LevelBricks;
};
