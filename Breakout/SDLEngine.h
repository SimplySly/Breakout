#pragma once

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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
#pragma comment (lib, "SDL2_mixer.lib")
#pragma comment (lib, "SDL2_ttf.lib")

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

#define DEFAULT_FONT			"Fonts/GameBoy.ttf"
#define LEVEL_LIST_FILE			"Data/LevelList.txt"

#define LEVEL_DISPLAY_TEXTURE	"Textures/state/LevelDisplay.jpg"
#define WIN_TEXTURE				"Textures/state/win.jpg"
#define LOSE_TEXTURE			"Textures/state/lose.jpg"
#define HUD_TEXT_COLOR			{255, 255, 255, 255}

//ball will bounce off paddle in opposite direction if it hits edge of paddle
//#define OPPOSITE_DIRECTION_VIA_EDGE	

//if paddle and ball have speed in contra directions on X axis, ball will bounce off paddle in opposite direction
//#define OPPOSITE_DIRECTION_VIA_SPEED	 

enum GAME_STATE {
	GAME_STATE_LEVEL_DISPLAY = 0,
	GAME_STATE_PAUSE,
	GAME_STATE_PLAYING,
	GAME_STATE_LOSE,
	GAME_STATE_WIN,
	GAME_STATE_QUIT
};


class SDLEngine
{
public:
	SDLEngine();
	SDLEngine(int ScreenWidth, int ScreenHeight);
	~SDLEngine();

	bool Init();

	void Loop();
private:
	bool LoadLevelObjects(const std::string& level);
	void ClearLevelObjects();
	bool InitGameState(); 
	bool LoadLevelList();

	void RenderSprite(Sprite* sprite);

	bool BounceOppositeDirection(float distanceX, const Vector2& ballDirection);
	bool BallBoundaryUpdate(float ballDeltaX, float ballDeltaY, bool& flipX, bool& flipY);
	void BounceBallOffPaddle();
	void UpdatePlayingState();

	void ResetGameObjects();
	void BallDeath();
	void LevelWin();

	void RenderGame(); 
	void RenderHUD(); 
	void RenderLevelDisplay();
	void RenderTexture(SDL_Texture* pTexture);
	void Update();
	void Render();

	//The window we'll be rendering to
	SDL_Window* m_Window;

	//The surface contained by the window
	SDL_Surface* m_ScreenSurface;

	//The window renderer
	SDL_Renderer* m_Renderer;

	TTF_Font* m_Font;

	int m_ScreenWidth, m_ScreenHeight;
	int m_PlayableScreenWidth, m_PlayableScreenHeight;
	Input *m_Input;
	GameTimer m_Timer;


	bool m_UpdateHud;
	SDL_Color m_HudTextColor;
	LevelInfo m_LevelInfo;
	PlayerInfo m_PlayerInfo;
	GAME_STATE m_GameState;
	std::vector<std::string> m_LevelList;

	GameObject *m_Paddle, *m_Ball;
	TextureCollection m_GameTextures;
	std::vector<Brick> m_LevelBricks;
};
