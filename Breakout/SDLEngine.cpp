#include "SDLEngine.h"

using namespace std;

SDLEngine::SDLEngine()
{
	m_Window = nullptr;
	m_ScreenSurface = nullptr;
	m_Renderer = nullptr;
	m_Texture = nullptr;
	
	m_Input = nullptr;
	m_paddle = nullptr;

	m_ScreenWidth = SCREEN_WIDTH;
	m_ScreenHeight = SCREEN_HEIGHT;
}

SDLEngine::SDLEngine(int ScreenWidth, int ScreenHeight) : SDLEngine()
{
	m_ScreenWidth = ScreenWidth;
	m_ScreenHeight = m_ScreenHeight;
}

SDLEngine::~SDLEngine()
{
	if (m_Input)
	{
		delete m_Input;
	}
	if (m_paddle)
	{
		delete m_paddle;
	}

	//Free loaded image
	SDL_DestroyTexture(m_Texture);
	m_Texture = nullptr;

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

bool SDLEngine::LoadMedia()
{
	m_Texture = LoadTexture("Textures/wood.png");
	if (m_Texture == nullptr)
	{
		printf("Failed to load texture image!\n");
		return false;
	}

	return true;
}

SDL_Texture* SDLEngine::LoadTexture(string path)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return nullptr;
	}

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
	if (newTexture == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

void SDLEngine::RenderSprite(Sprite *sprite)
{
	if (sprite == nullptr)
	{
		return;
	}

	SDL_Rect renderQuad = { (int)sprite->PositionX, (int)sprite->PositionY, sprite->Width, sprite->Height};

	//Render to screen
	SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &renderQuad);
}

bool SDLEngine::LoadObjects()
{
	m_paddle = new Sprite(m_ScreenWidth / 2 - 50, m_ScreenHeight * 29 / 30 - 10, 100, 20, 0);
	if (m_paddle == nullptr)
	{
		return false;
	}

	return true;
}

void SDLEngine::Update()
{
	if (m_Input->IsKeyDown(SDLK_LEFT))
	{
		if (m_paddle->PositionX > 0.f)
		{
			m_paddle->PositionX -= 0.1f;
		}
	}
	if (m_Input->IsKeyDown(SDLK_RIGHT))
	{
		if ((int)m_paddle->PositionX + m_paddle->Width < m_ScreenWidth)
		{
			m_paddle->PositionX += 0.1f;
		}
	}
}

void SDLEngine::Render()
{
	//Clear screen
	SDL_RenderClear(m_Renderer);

	RenderSprite(m_paddle);

	//Update screen
	SDL_RenderPresent(m_Renderer);
}

void SDLEngine::Loop()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

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
