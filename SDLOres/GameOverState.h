#pragma once
#include"States.h"

#include <SDL.h>
#undef main

class ImageObj;
class StateMachine;
class GameOverState: public State
{
public:
	GameOverState(SDL_Renderer* render, StateMachine* machine);
	~GameOverState();
	virtual void init();
	virtual void handleEvents();
	virtual void update();
	virtual void render();
	void destroyObjects();
private:
	SDL_Renderer* renderer;
	ImageObj* gameOverScreen;
	ImageObj* replayButton;
	StateMachine* machine;
	bool objectsDestroyed = false;
};