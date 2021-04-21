#include "SDLEngine.h"

using namespace std;

SDLEngine::SDLEngine()
{
	m_Window = nullptr;
	m_ScreenSurface = nullptr;
	m_Renderer = nullptr;
	m_Font = nullptr;

	m_Input = nullptr;

	m_Paddle = nullptr;
	m_Ball = nullptr;

	m_ScreenWidth = SCREEN_WIDTH;
	m_ScreenHeight = SCREEN_HEIGHT;

	m_HudTextColor = HUD_TEXT_COLOR;
	m_UpdateHud = false;

	m_PlayableScreenWidth = m_ScreenWidth;
	m_PlayableScreenHeight = m_ScreenHeight - HUD_HEIGHT;
}

SDLEngine::SDLEngine(int ScreenWidth, int ScreenHeight) : SDLEngine()
{
	m_ScreenWidth = ScreenWidth;
	m_ScreenHeight = ScreenHeight;

	m_PlayableScreenWidth = ScreenWidth;
	m_PlayableScreenHeight = ScreenHeight - HUD_HEIGHT;
}

SDLEngine::~SDLEngine()
{
	if (m_Input)
	{
		delete m_Input;
		m_Input = nullptr;
	}
	if (m_Paddle)
	{
		delete m_Paddle;
		m_Paddle = nullptr;
	}
	if (m_Ball)
	{
		delete m_Ball;
		m_Ball = nullptr;
	}

	//Free font
	TTF_CloseFont(m_Font);
	m_Font = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool SDLEngine::Init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

		return false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	//Open the font
	m_Font = TTF_OpenFont(DEFAULT_FONT, 28);
	if (m_Font == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Get window surface
	m_ScreenSurface = SDL_GetWindowSurface(m_Window);

	m_Input = new Input();
	if (m_Input == nullptr)
	{
		return false;
	}

	if (!InitGameState())
	{
		return false;
	}
	if (!LoadLevelList())
	{
		return false;
	}

	return true;
}


bool SDLEngine::InitGameState()
{
	m_PlayerInfo.SetToDefault();

	m_GameState = GAME_STATE_LEVEL_DISPLAY;

	m_GameTextures.LoadTexture(LEVEL_DISPLAY_TEXTURE, m_Renderer, "LevelDisplay");
	m_GameTextures.LoadTexture(WIN_TEXTURE, m_Renderer, "Win");
	m_GameTextures.LoadTexture(LOSE_TEXTURE, m_Renderer, "Lose");

	m_GameTextures.AddFontTexture(string("LEVEL ") + to_string(m_PlayerInfo.CurrentLevel), "LevelNumber", m_Renderer, m_Font, m_HudTextColor);
	m_GameTextures.AddFontTexture(string("LIFE ") + to_string(m_PlayerInfo.Life), "Life", m_Renderer, m_Font, m_HudTextColor);
	m_GameTextures.AddFontTexture(string("SCORE ") + to_string(m_PlayerInfo.Life), "Score", m_Renderer, m_Font, m_HudTextColor);
	

	return true;
}

bool SDLEngine::LoadLevelList()
{
	m_LevelList.push_back("Levels/Level0.xml");
	m_LevelList.push_back("Levels/Level1.xml");

	return true;
}

SDL_Texture* SDLEngine::LoadTexture(string path)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
	if (texture == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(loadedSurface);

	return texture;
}

void SDLEngine::ClearLevelObjects()
{
	if (m_Paddle)
	{
		delete m_Paddle;
		m_Paddle = nullptr;
	}
	if (m_Ball)
	{
		delete m_Ball;
		m_Ball = nullptr;
	}

	m_LevelTextures.Clear();
	m_Sounds.Clear();
	m_LevelBricks.clear();
}

bool SDLEngine::LoadLevelObjects(string levelPath)
{
	if (!m_LevelTextures.LoadTexture("Textures/paddle/paddle_wood.png", m_Renderer))
	{
		return false;
	}

	m_Paddle = new GameObject();
	m_Paddle->SpeedX = 0.0f;
	m_Paddle->SpeedY = 0.0f;
	m_Paddle->sprite = Sprite((float)m_PlayableScreenWidth / 2 - PADDLE_WIDTH / 2, (float)m_PlayableScreenHeight * 29 / 30 - 10, PADDLE_WIDTH, PADDLE_HEIGHT, 0);

	if (!m_LevelTextures.LoadTexture("Textures/ball/ball.png", m_Renderer))
	{
		return false;
	}

	m_Ball = new GameObject();
	m_Ball->SpeedX = BALL_SPEED_X;
	m_Ball->SpeedY = BALL_SPEED_Y;
	m_Ball->sprite = Sprite((float)m_PlayableScreenWidth / 2 - BALL_RADIUS / 2, (float)m_PlayableScreenHeight / 2 - BALL_RADIUS / 2, BALL_RADIUS, BALL_RADIUS, 1);

	XMLLevelLoader level;

	if (!level.LoadFromXML(levelPath, m_LevelInfo, m_LevelBricks, m_LevelTextures,
		m_Renderer, m_Sounds, m_PlayableScreenWidth, m_PlayableScreenHeight))
	{
		return false;
	}

	return true;
}

void SDLEngine::ResetGameObjects()
{
	m_Paddle->SpeedX = 0.0f;
	m_Paddle->SpeedY = 0.0f;
	m_Paddle->sprite.PositionX = (float)m_PlayableScreenWidth / 2 - m_Paddle->sprite.Width / 2;
	m_Paddle->sprite.PositionY = (float)m_PlayableScreenHeight * 29 / 30 - m_Paddle->sprite.Height / 2;

	m_Ball->SpeedX = BALL_SPEED_X;
	m_Ball->SpeedY = BALL_SPEED_Y;
	m_Ball->sprite.PositionX = (float)m_PlayableScreenWidth / 2 - BALL_RADIUS / 2;
	m_Ball->sprite.PositionY = (float)m_PlayableScreenHeight / 2 - BALL_RADIUS / 2;
}

void SDLEngine::BallDeath()
{
	m_UpdateHud = true;
	m_PlayerInfo.Life--;
	if (m_PlayerInfo.Life < 1)
	{
		m_GameState = GAME_STATE_LOSE;
		ClearLevelObjects();

		return;
	}

	ResetGameObjects();
	m_GameState = GAME_STATE_PAUSE;
}


void SDLEngine::LevelWin()
{
	m_PlayerInfo.CurrentLevel++;
	m_GameTextures.UpdateFontTexture("LEVEL " + to_string(m_PlayerInfo.CurrentLevel), "LevelNumber", m_Renderer, m_Font, m_HudTextColor);
	ClearLevelObjects();
	if (m_PlayerInfo.CurrentLevel > m_LevelList.size())
	{
		m_GameState = GAME_STATE_WIN;
	}
	else
	{
		m_GameState = GAME_STATE_LEVEL_DISPLAY;
	}
}

bool SDLEngine::BallBoundaryUpdate(float ballDeltaX, float ballDeltaY, bool& flipX, bool& flipY)
{
	if (m_Ball->SpeedX > 0)
	{
		if (m_Ball->sprite.right() + ballDeltaX > m_PlayableScreenWidth)
		{
			flipX = true;

			return false;
		}
	}
	if (m_Ball->SpeedX < 0)
	{
		if (m_Ball->sprite.left() + ballDeltaX < 0)
		{
			flipX = true;

			return false;
		}
	}

	if (m_Ball->SpeedY < 0)
	{
		if (m_Ball->sprite.top() + ballDeltaY < 0)
		{
			flipY = true;

			return false;
		}
	}
	if (m_Ball->SpeedY > 0)
	{
		if (m_Ball->sprite.bottom() + ballDeltaY > m_PlayableScreenHeight)
		{
			BallDeath();

			return true;
		}
	}

	return false;
}

bool SDLEngine::BounceOppositeDirection(float distanceX, Vector2 ballDirection)
{
#if defined(OPPOSITE_DIRECTION_VIA_EDGE)
	if (fabs(distanceX) > m_Paddle->sprite.Width / 4)
	{

		if (atanf(fabs(ballDirection.y / ballDirection.x)) < PI / 3.0f)
		{

			m_Ball->SpeedX = ballDirection.x;
			m_Ball->SpeedY = ballDirection.y;

			return true;
		}
	}
#elif defined(OPPOSITE_DIRECTION_VIA_SPEED)
	cout << "called" << endl;
	if (m_Ball->SpeedX > 0.0f && m_Paddle->SpeedX < 0.0f
		|| m_Ball->SpeedX < 0.0f && m_Paddle->SpeedX > 0.0f)
	{
		m_Ball->SpeedX = ballDirection.x;
		m_Ball->SpeedY = ballDirection.y;

		return true;
	}
#endif

	return false;
}


void SDLEngine::BounceBallOffPaddle()
{
	Vector2 bounceNormal(0.0f, -400.0f);
	Vector2 ballDirection(-m_Ball->SpeedX, -m_Ball->SpeedY);


	float distanceX = m_Ball->sprite.centerX() - m_Paddle->sprite.centerX();
	float rotateBounceNormalAngle = (distanceX / m_Paddle->sprite.Width / 2) * MAX_NORMAL_ROTATION;

	if (BounceOppositeDirection(distanceX, ballDirection))
	{
		return;
	}

	bounceNormal.rotate(rotateBounceNormalAngle);
	bounceNormal.reflect(ballDirection);


	if (ballDirection.y > 0)
	{
		ballDirection.y = -ballDirection.y;
	}

	m_Ball->SpeedX = ballDirection.x;
	m_Ball->SpeedY = ballDirection.y;
}

void SDLEngine::UpdatePlayingState()
{
	/*PADDLE UPDATE*/
	float TimeDelta = m_Timer.GetTicks() / 1000.0f;
	float PaddleSpeed = PADDLE_SPEED;

	if (m_Input->IsKeyDown(SDLK_LEFT))
	{
		m_Paddle->SpeedX = -PaddleSpeed;
	}
	else if (m_Input->IsKeyDown(SDLK_RIGHT))
	{
		m_Paddle->SpeedX = PaddleSpeed;
	}
	else
	{
		m_Paddle->SpeedX = 0.0f;
	}

	float paddleDeltaX = m_Paddle->SpeedX * TimeDelta;
	if (m_Paddle->SpeedX > 0.0f)
	{
		if ((int)m_Paddle->sprite.right() + paddleDeltaX < m_ScreenWidth)
		{
			m_Paddle->sprite.PositionX += paddleDeltaX;
		}
	}

	if (m_Paddle->SpeedX < 0.0f)
	{
		if ((int)m_Paddle->sprite.left() + paddleDeltaX > 0)
		{
			m_Paddle->sprite.PositionX += paddleDeltaX;
		}
	}


	/*BALL UPDATE*/
	float ballDeltaX = TimeDelta * m_Ball->SpeedX;
	float ballDeltaY = TimeDelta * m_Ball->SpeedY;


	bool flipX = false, flipY = false;

	if (BallBoundaryUpdate(ballDeltaX, ballDeltaY, flipX, flipY))
	{
		return;
	}

	Sprite newPos;

	newPos.PositionX = m_Ball->sprite.PositionX + TimeDelta * m_Ball->SpeedX;
	newPos.PositionY = m_Ball->sprite.PositionY + TimeDelta * m_Ball->SpeedY;
	newPos.Width = m_Ball->sprite.Width;
	newPos.Height = m_Ball->sprite.Height;

	for (auto& brick : m_LevelBricks)
	{
		if (brick.IsActive)
		{
			auto collision = CircleAndRect(newPos, brick.sprite);
			if (collision == COLLISION_NONE)
			{
				continue;
			}

			Mix_PlayChannel(-1, m_Sounds[brick.HitSoundIndex], 0);
			brick.DecreaseHitPoints();
			if (!brick.IsActive)
			{
				Mix_PlayChannel(-1, m_Sounds[brick.BreakSoundIndex], 0);

				m_PlayerInfo.Score += brick.Score;
				m_LevelInfo.BricksToDestroy--;
				m_UpdateHud = true;

				if (m_LevelInfo.BricksToDestroy < 1)
				{
					LevelWin();

					return;
				}
			}

			if (collision == COLLISION_LEFT || collision == COLLISION_RIGHT)
			{
				flipX = true;
			}
			if (collision == COLLISION_TOP || collision == COLLISION_BOTTOM)
			{
				flipY = true;
			}
		}
	}


	auto collision = CircleAndRect(newPos, m_Paddle->sprite);
	if (collision != COLLISION_NONE)
	{
		if (collision == COLLISION_LEFT || collision == COLLISION_RIGHT)
		{
			flipX = true;
		}
		if (collision == COLLISION_TOP)
		{
			BounceBallOffPaddle();
		}
	}

	if (flipX)
	{
		m_Ball->SpeedX = -m_Ball->SpeedX;
	}
	if (flipY)
	{
		m_Ball->SpeedY = -m_Ball->SpeedY;
	}


	m_Ball->sprite.PositionX += TimeDelta * m_Ball->SpeedX;
	m_Ball->sprite.PositionY += TimeDelta * m_Ball->SpeedY;
}


void SDLEngine::Update()
{
	/*	switch looks ugly
		eventhough this whole code looks ugly, I wanted something to look pretty
		anyway who cares */
	if (m_GameState == GAME_STATE_PLAYING)
	{
		UpdatePlayingState();

		return;
	}
	if (m_GameState == GAME_STATE_PAUSE)
	{
		m_Timer.Pause();

		if (m_Input->IsKeyDown(SDLK_SPACE) || m_Input->IsKeyDown(SDLK_RETURN))
		{
			m_GameState = GAME_STATE_PLAYING;
			m_Timer.Start();
		}

		return;
	}
	if (m_GameState == GAME_STATE_LEVEL_DISPLAY)
	{
		if (m_Input->IsKeyDown(SDLK_SPACE) || m_Input->IsKeyDown(SDLK_RETURN))
		{
			m_GameState = GAME_STATE_PAUSE;
			if (!LoadLevelObjects(m_LevelList[m_PlayerInfo.CurrentLevel - 1]))
			{
				m_GameState = GAME_STATE_QUIT;
				cout << "corrupted game data!" << endl;
			}
		}

		return;
	}

	if (m_GameState == GAME_STATE_LOSE)
	{
		if (m_Input->IsKeyDown(SDLK_SPACE) || m_Input->IsKeyDown(SDLK_RETURN))
		{
			m_GameState = GAME_STATE_LEVEL_DISPLAY;
			m_PlayerInfo.SetToDefault();
			SDL_Delay(100);
		}

		return;
	}

	if (m_GameState == GAME_STATE_WIN)
	{
		if (m_Input->IsKeyDown(SDLK_SPACE) || m_Input->IsKeyDown(SDLK_RETURN))
		{
			m_GameState = GAME_STATE_QUIT;
		}

		return;
	}
}

void SDLEngine::RenderSprite(const Sprite* sprite)
{
	if (sprite == nullptr)
	{
		return;
	}

	SDL_Rect renderQuad = { (int)sprite->PositionX, (int)sprite->PositionY, sprite->Width, sprite->Height };

	//Render to screen
	SDL_RenderCopy(m_Renderer, m_LevelTextures[sprite->TextureIndex].pTexture, nullptr, &renderQuad);
}

void SDLEngine::RenderHUD()
{
	if (m_UpdateHud)
	{
		m_UpdateHud = false;

	}
	//SDL_Rect renderRect = { m_ScreenWidth / 2 -,
	//	m_ScreenHeight / 2 - pLevelNumberTexture.Height / 2,
	//	pLevelNumberTexture.Height };
	//SDL_RenderCopy(m_Renderer, pLevelNumberTexture.pTexture, nullptr, &renderRect);

}

void SDLEngine::RenderGame()
{
	//Clear screen
	SDL_RenderClear(m_Renderer);

	SDL_RenderCopy(m_Renderer, m_LevelTextures[m_LevelInfo.BackgroundTextureIndex].pTexture, nullptr, nullptr);

	for (auto& brick : m_LevelBricks)
	{
		if (brick.IsActive)
		{
			RenderSprite(&brick.sprite);
		}
	}

	RenderSprite(&m_Paddle->sprite);

	RenderSprite(&m_Ball->sprite);

	//Update screen
	SDL_RenderPresent(m_Renderer);
}

void SDLEngine::RenderTexture(SDL_Texture* pTexture)
{
	SDL_RenderClear(m_Renderer);

	SDL_RenderCopy(m_Renderer, pTexture, nullptr, nullptr);

	//Update screen
	SDL_RenderPresent(m_Renderer);
}

void SDLEngine::RenderLevelDisplay()
{
	SDL_RenderClear(m_Renderer);

	SDL_RenderCopy(m_Renderer, m_GameTextures["LevelDisplay"].pTexture, nullptr, nullptr);

	const Texture& pLevelNumberTexture = m_GameTextures["LevelNumber"];
	SDL_Rect renderRect = { m_ScreenWidth / 2 - pLevelNumberTexture.Width / 2,
		m_ScreenHeight / 2 - pLevelNumberTexture.Height / 2,
		pLevelNumberTexture.Width,
		pLevelNumberTexture.Height };
	SDL_RenderCopy(m_Renderer, pLevelNumberTexture.pTexture, nullptr, &renderRect);

	//Update screen
	SDL_RenderPresent(m_Renderer);
}

void SDLEngine::Render()
{
	if (m_GameState == GAME_STATE_PLAYING || m_GameState == GAME_STATE_PAUSE)
	{
		RenderGame();

		return;
	}

	if (m_GameState == GAME_STATE_LEVEL_DISPLAY)
	{
		RenderLevelDisplay();

		return;
	}

	if (m_GameState == GAME_STATE_WIN)
	{
		RenderTexture(m_GameTextures["Win"].pTexture);

		return;
	}

	if (m_GameState == GAME_STATE_LOSE)
	{
		RenderTexture(m_GameTextures["Lose"].pTexture);

		return;
	}
}

void SDLEngine::Loop()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit && m_GameState != GAME_STATE_QUIT)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//Input keydown
			if (e.type == SDL_KEYDOWN)
			{
				m_Input->KeyDown(e.key.keysym.sym);

				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
			}
			if (e.type == SDL_KEYUP)
			{
				m_Input->KeyUp(e.key.keysym.sym);
			}
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		Update();
		Render();
	}
}
