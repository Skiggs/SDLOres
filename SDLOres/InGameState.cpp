#include"Game.h"
#include"TextureManager.h"
#include"GameObject.h"
#include"GridManager.h"
#include"InGameState.h"
#include"StateMachine.h"
#include"GameOverState.h"

InGameState::InGameState(SDL_Renderer* render,StateMachine* mach)
{
	renderer = render;
	machine = mach;
}

void InGameState::init()
{
	char* path = SDL_GetBasePath();
	char endpointdest[20] = "images/EndZone.bmp";
	strcat(path, endpointdest);
	endPoint = new ImageObj(path, renderer, 50, 400, Vector2D(200, 200));
	grid = new Grid(renderer, endPoint->getPosition());
}

InGameState::~InGameState()
{
	delete endPoint;
	grid->~Grid();
}

void InGameState::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		break;

	default:
		break;
	}
}

void InGameState::update()
{
	grid->update();

	if (grid->checkIfReachedEndpoint())
	{
		desroyObjects();
		machine->AddState(StateRef(new GameOverState(renderer,machine)));
	}
}

void InGameState::desroyObjects()
{
     endPoint->~ImageObj();
	 grid->~Grid();
	objectsdestroyed = true;
}

void InGameState::render()
{
	SDL_RenderClear(renderer);

	if (!objectsdestroyed)
	{
		grid->render();
		endPoint->render();
	}
	// Finally show what we've drawn
	SDL_RenderPresent(renderer);
}