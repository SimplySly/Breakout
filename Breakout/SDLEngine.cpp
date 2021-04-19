#include "SDLEngine.h"

using namespace std;

SDLEngine::SDLEngine()
{
	m_Window = nullptr;
	m_ScreenSurface = nullptr;
	m_Renderer = nullptr;
	
	m_Input = nullptr;

	m_Paddle = nullptr;
	m_Ball = nullptr;

	m_ScreenWidth = SCREEN_WIDTH;
	m_ScreenHeight = SCREEN_HEIGHT;

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

	//Destroy window	
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

bool SDLEngine::Init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Get window surface
	m_ScreenSurface = SDL_GetWindowSurface(m_Window);

	m_Input = new Input();

	return true;
}

void SDLEngine::ClearLevelObjects()
{
	if (m_Paddle)
	{
		delete m_Paddle;
	}
	if (m_Ball)
	{
		delete m_Ball;
	}

	m_Textures.Clear();
	m_LevelBricks.clear();
}

bool SDLEngine::LoadLevelObjects(string levelPath)
{
	if (!m_Textures.LoadTexture("Textures/paddle/paddle_wood.png", m_Renderer))
	{
		return false;
	}

	m_Paddle = new GameObject();
	m_Paddle->SpeedX = 0.0f;
	m_Paddle->SpeedY = 0.0f;
	m_Paddle->sprite = Sprite((float)m_PlayableScreenWidth / 2 - 50, (float)m_PlayableScreenHeight * 29 / 30 - 10, 100, 20, 0);
	
	if (!m_Textures.LoadTexture("Textures/ball/ball.png", m_Renderer))
	{
		return false;
	}

	m_Ball = new GameObject();
	m_Ball->SpeedX = BALL_SPEED_X;
	m_Ball->SpeedY = BALL_SPEED_Y;
	m_Ball->sprite = Sprite((float)m_PlayableScreenWidth / 2, (float)m_PlayableScreenHeight / 2, 20, 20, 1);

	XMLLevelLoader level;

	if (!level.LoadFromXML(levelPath, m_LevelInfo, m_LevelBricks, m_Textures, m_Renderer, m_PlayableScreenWidth, m_PlayableScreenHeight))
	{
		return false;
	}

	return true;
}

void SDLEngine::RenderSprite(const Sprite* sprite)
{
	if (sprite == nullptr)
	{
		return;
	}

	SDL_Rect renderQuad = { (int)sprite->PositionX, (int)sprite->PositionY, sprite->Width, sprite->Height };

	//Render to screen
	SDL_RenderCopy(m_Renderer, m_Textures[sprite->TextureIndex], nullptr, &renderQuad);
}

void SDLEngine::Update()
{
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

	float ballDeltaX = TimeDelta * m_Ball->SpeedX;
	float ballDeltaY = TimeDelta * m_Ball->SpeedY;
	// boundaries
	if (m_Ball->SpeedX > 0)
	{
		if (m_Ball->sprite.right() + ballDeltaX > m_PlayableScreenWidth)
		{
			m_Ball->SpeedX = -m_Ball->SpeedX;
		}
	}
	if (m_Ball->SpeedX < 0)
	{
		if (m_Ball->sprite.left() + ballDeltaX  < 0)
		{
			m_Ball->SpeedX = -m_Ball->SpeedX;
		}
	}

	if (m_Ball->SpeedY < 0)
	{
		if (m_Ball->sprite.top() + ballDeltaY < 0)
		{
			m_Ball->SpeedY = -m_Ball->SpeedY;
		}
	}
	if (m_Ball->SpeedY > 0)
	{
		if (m_Ball->sprite.bottom() + ballDeltaY > m_PlayableScreenHeight)
		{
			m_Ball->SpeedY = -m_Ball->SpeedY;

			//Life Loss Respawn
		}
	}

	m_Ball->sprite.PositionX += TimeDelta * m_Ball->SpeedX;
	m_Ball->sprite.PositionY += TimeDelta * m_Ball->SpeedY;
}

void SDLEngine::Render()
{
	//Clear screen
	SDL_RenderClear(m_Renderer);

	SDL_RenderCopy(m_Renderer, m_Textures[m_LevelInfo.BackgroundTextureIndex], nullptr, nullptr);

	for (const auto &brick : m_LevelBricks)
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

void SDLEngine::Loop()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	
	m_Timer.Start();

	//While application is running
	while (!quit)
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
