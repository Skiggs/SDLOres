#pragma once
#include"States.h"
#include <SDL.h>
#undef main


class Box;
class Grid;
class ImageObj;
class StateMachine;

class InGameState : public State
{
public:
	InGameState(SDL_Renderer* render, StateMachine* machine);
	~InGameState();
	virtual void init();
	virtual void handleEvents();
	virtual void update();
	virtual void render();
	void desroyObjects();
private:
	SDL_Renderer* renderer;
	ImageObj* endPoint;
	Grid* grid;
	StateMachine* machine;
	bool objectsdestroyed = false;
};