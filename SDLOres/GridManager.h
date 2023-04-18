#pragma once

#include"GameObject.h"
#include<vector>
#include<array>

const int initialRowXPos = 800;
const int initialRowYPos = 600;

class Grid
{
public:
	Grid(SDL_Renderer* renderer, Vector2D endPos);
	~Grid();

	void update();
	void render();
	void calculateBoxesToRemove(int row, int column);
	void refreshGrid();
	void pushAndAddRow();
	bool checkIfReachedEndpoint();
private:
	SDL_Renderer* ren;
	std::function<void(int, int)> cb;
	std::vector<std::vector<Box*>> grid;
	float clickDelayTimer = 0.0f;
	float gridPushTime = 20.0f;
	Vector2D endPosition;
};