#pragma once

#ifndef Game_h
#define Game_h

#include <SDL.h>
#undef main
#include<stdio.h>
#include"StateMachine.h"


class Box;
class Grid;
class ImageObj;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update(float dt);
	void render(float dt);
	void clean();
	void loop();
	bool running() const { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const float dt = 1.0f / 60.0f;
	SDL_Rect ab;
	SDL_Texture* tex = nullptr;
	Box* firstBox;
	ImageObj* endPoint;
	Grid* grid;
	StateMachine machine;
};


#endif