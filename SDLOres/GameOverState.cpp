#include"GameOverState.h"
#include"Game.h"
#include"TextureManager.h"
#include"GameObject.h"
#include"GridManager.h"
#include"StateMachine.h"
#include"InGameState.h"

GameOverState::GameOverState(SDL_Renderer* render, StateMachine* mach)
{
	renderer = render;
	machine = mach;
}

void GameOverState::init()
{
	char* path = SDL_GetBasePath();
	char* path2 = SDL_GetBasePath();

	for (int j = 0; j < strlen(path); ++j)
	{
		if (path[j] == '\\')
		{
			path[j] = '/';
		}
	}

	char gameoverdest[20] = "images/GameOver.bmp";
	char replayButtondest[20] = "images/Replay.bmp";

	strcat(path, gameoverdest);
	strcat(path2, replayButtondest);

	gameOverScreen = new ImageObj(path, renderer, 800, 800, Vector2D(200, 100));
	replayButton = new ImageObj(path2, renderer, 200, 100, Vector2D(500, 600));
}

GameOverState::~GameOverState()
{
	delete gameOverScreen;
	delete replayButton;
}

void GameOverState::handleEvents()
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

void GameOverState::destroyObjects()
{
	 gameOverScreen->~ImageObj();
	 replayButton->~ImageObj();
	objectsDestroyed = true;
}

void GameOverState::update()
{
	if (replayButton->checkIfMouseIsInside())
	{
		destroyObjects();
		machine->AddState(StateRef(new InGameState(renderer,machine)));
	}
}


void GameOverState::render()
{
	SDL_RenderClear(renderer);

	if (!objectsDestroyed)
	{
		gameOverScreen->render();
		replayButton->render();
	}
	// Finally show what we've drawn
	SDL_RenderPresent(renderer);
}
