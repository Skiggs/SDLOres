#include"Game.h"
#include"TextureManager.h"
#include"GameObject.h"
#include"GridManager.h"
#include"InGameState.h"



Game::Game()
{
	ab.h = 40;
	ab.w = 40;
	ab.x = 200;
	ab.y = 300;
}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 32, 0, 0, SDL_ALPHA_OPAQUE);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	machine.AddState(StateRef(new InGameState(renderer,&machine)));
	//endPoint = new ImageObj("../images/EndZone.bmp", renderer, 50, 400, Vector2D(200, 200));
	//grid = new Grid(7, renderer,endPoint->getPosition());
	////tex = TextureManager::LoadTexture("../images/Background.bmp", renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::loop()
{
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	while (isRunning)
	{
		machine.ProcessState();
		frameStart = SDL_GetTicks();

		machine.GetActiveState()->handleEvents();
		machine.GetActiveState()->update();
		machine.GetActiveState()->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

}

void Game::update(float dt)
{
	grid->update();
}

void Game::render(float dt)
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 32, 0, 0, SDL_ALPHA_OPAQUE);
	grid->render();
	// Do our drawing
	endPoint->render();

	// Finally show what we've drawn
	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}