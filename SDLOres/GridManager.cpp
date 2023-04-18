#include"GridManager.h"
#include<string>
#include<algorithm>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "libcmt.lib")

Grid::Grid(SDL_Renderer* render,Vector2D endPos)
{
	endPosition = endPos;
	ren = render;
	
	for (int i = 0; i < 7; ++i)
	{
		grid.push_back({});
		for (int j = 0; j < 10; ++j)
		{
			int rnd =  1;
			char* path = SDL_GetBasePath();
			for (int j = 0; j < strlen(path); ++j)
			{
				if (path[j] == '\\')
				{
					path[j] = '/';
				}
			}
			if (rnd == 1)
			{
				char bluedest[20] = "images/Blue.bmp";
				strcat(path, bluedest);
				grid[i].push_back(new Box(BoxColor::BLUE, i, j, path, render, std::bind(&Grid::calculateBoxesToRemove, this,std::placeholders::_1, std::placeholders::_2)));
			
			}

			else if (rnd == 2)
			{
				char greendest[20] = "images/Green.bmp";
				strcat(path, greendest);
				grid[i].push_back(new Box(BoxColor::GREEN, i, j, path, render, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		
			}

			else if (rnd == 3)
			{
				char orangedest[20] = "images/Orange.bmp";
				strcat(path, orangedest);
				grid[i].push_back(new Box(BoxColor::ORANGE, i, j, path, render, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		
			}

			else if (rnd == 4)
			{
				char reddest[20] = "images/Red.bmp";
				strcat(path, reddest);
				grid[i].push_back(new Box(BoxColor::RED, i, j, path, render, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		
			}

			grid[i][j]->setPosition(Vector2D((i * boxSize) + initialRowXPos + i, initialRowYPos - (j * boxSize)  - j));
		}

		
    }
}

Grid::~Grid()
{
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			delete grid[i][j];
		}
		grid[i].clear();
	}
	grid.clear();
}

void Grid::update()
{
	if (clickDelayTimer <= 0.0f && gridPushTime>0.0f)
	{
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[i].size(); ++j)
			{
				if (grid[i][j]->checkIfMouseIsInside())
				{
					clickDelayTimer = 3.0f;
					break;
				}
			}
		}
	}

	else
	{
		clickDelayTimer -= 0.1f;
	}

	if (gridPushTime <= 0.f)
	{
		pushAndAddRow();
		gridPushTime = 20.0f;
	}

	else
	{
		gridPushTime -= 0.05f;
	}
}

bool Grid::checkIfReachedEndpoint()
{
	if (grid.size() > 0)
	{
		if (grid[0].size() > 0)
		{
			if (grid[0][0]->getPosition().x < endPosition.x + 100)
				return true;
		}
	}

	return false;
}

void Grid::pushAndAddRow()
{

	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			grid[i][j]->setPosition(Vector2D(grid[i][j]->getPosition().x - boxSize, grid[i][j]->getPosition().y));
		}
	}
	grid.push_back({});

	int gridsize = grid.size() - 1;
	for (int i = 0; i < 10; ++i)
	{
		int rnd = rand() % 4 + 1;

		char* path = SDL_GetBasePath();
		for (int j = 0; j < strlen(path); ++j)
		{
			if (path[j] == '\\')
			{
				path[j] = '/';
			}
		}

		if (rnd == 1)
		{
			char bluedest[20] = "images/Blue.bmp";
			strcat(path, bluedest);
			grid[gridsize].push_back(new Box(BoxColor::BLUE, gridsize, i, path, ren, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		}

		else if (rnd == 2)
		{
			char greendest[20] = "images/Green.bmp";
			strcat(path, greendest);
			grid[gridsize].push_back(new Box(BoxColor::GREEN, gridsize, i, path, ren, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		}

		else if (rnd == 3)
		{
			char orangedest[20] = "images/Orange.bmp";
			strcat(path, orangedest);
			grid[gridsize].push_back(new Box(BoxColor::ORANGE, gridsize, i, path, ren, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		}

		else if (rnd == 4)
		{
			char reddest[20] = "images/Red.bmp";
			strcat(path, reddest);
			grid[gridsize].push_back(new Box(BoxColor::RED, gridsize, i, path, ren, std::bind(&Grid::calculateBoxesToRemove, this, std::placeholders::_1, std::placeholders::_2)));
		}

		grid[gridsize][i]->setPosition(Vector2D(grid[gridsize-1][0]->getPosition().x + boxSize + 1, initialRowYPos - (i * boxSize) - i));
	}


}

void Grid::render()
{
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			grid[i][j]->render();
		}
	}
}

void Grid::calculateBoxesToRemove(int row, int column)
{
	std::vector<Box*> boxesToErase, collectedBoxed;
	boxesToErase.push_back(grid[row][column]);
	grid[row][column]->isCollected = true;
	std::vector<Box*>::iterator it = boxesToErase.begin();
	bool canBeRemoved = false;

	while (it != boxesToErase.end())
	{
		if ((*it)->boxrow -1>=0 && (*it)->boxcolumn < grid[(size_t)(*it)->boxrow - 1].size() && !grid[(size_t)(*it)->boxrow - 1][(*it)->boxcolumn]->isCollected &&
			(*it)->getColor() == grid[(size_t)(*it)->boxrow - 1][(*it)->boxcolumn]->getColor())
		{
			boxesToErase.push_back(grid[(size_t)(*it)->boxrow - 1][(*it)->boxcolumn]);
			it = boxesToErase.begin();
			grid[(size_t)(*it)->boxrow - 1][(*it)->boxcolumn]->isCollected = true;
			canBeRemoved = true;
		}

		if ((*it)->boxcolumn - 1 >= 0  && !grid[(size_t)(*it)->boxrow][(size_t)(*it)->boxcolumn - 1]->isCollected 
			&& (*it)->getColor() == grid[(*it)->boxrow][(size_t)(*it)->boxcolumn - 1]->getColor())
		{
			boxesToErase.push_back(grid[(*it)->boxrow][(size_t)(*it)->boxcolumn -1]);
			it = boxesToErase.begin();
			grid[(size_t)(*it)->boxrow][(size_t)(*it)->boxcolumn - 1]->isCollected = true;
			canBeRemoved = true;
		}

		if ((size_t)(*it)->boxrow + 1 <grid.size() && (*it)->boxcolumn < grid[(size_t)(*it)->boxrow + 1].size() && !grid[(size_t)(*it)->boxrow + 1][(*it)->boxcolumn]->isCollected 
			&& (*it)->getColor() == grid[(size_t)(*it)->boxrow + 1][(*it)->boxcolumn]->getColor())
		{
			boxesToErase.push_back(grid[(size_t)(*it)->boxrow + 1][(*it)->boxcolumn]);
			it = boxesToErase.begin();
			grid[(size_t)(*it)->boxrow + 1][(*it)->boxcolumn]->isCollected = true;
			canBeRemoved = true;
		}

		if ((size_t)(*it)->boxcolumn + 1 < grid[(size_t)(*it)->boxrow].size() && !grid[(size_t)(*it)->boxrow][(size_t)(*it)->boxcolumn + 1]->isCollected
			&& (*it)->getColor() == grid[(*it)->boxrow][(size_t)(*it)->boxcolumn + 1]->getColor())
		{
			boxesToErase.push_back(grid[(*it)->boxrow][(size_t)(*it)->boxcolumn + 1]);
			it = boxesToErase.begin();
			grid[(size_t)(*it)->boxrow][(size_t)(*it)->boxcolumn + 1]->isCollected = true;
			canBeRemoved = true;
		}

		if (canBeRemoved)
		{
			collectedBoxed.push_back(*it);
			//grid[(*it)->boxrow].begin() + (*it)->boxcolumn
		
		}
		boxesToErase.erase(it);
		it = boxesToErase.begin();

	}

	for (int i = 0; i < collectedBoxed.size(); ++i)
	{
		grid[collectedBoxed[i]->boxrow].erase(grid[collectedBoxed[i]->boxrow].begin() + collectedBoxed[i]->boxcolumn);
		for (int j = 0; j < grid[collectedBoxed[i]->boxrow].size(); ++j)
		{
			grid[collectedBoxed[i]->boxrow][j]->boxcolumn = j;
		}
		delete collectedBoxed[i];
	}

	refreshGrid();
}

void Grid::refreshGrid()
{
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			grid[i][j]->setPosition(Vector2D(grid[i][j]->getPosition().x, initialRowYPos - (j * boxSize) - j));
			grid[i][j]->isCollected = false;
		}
	}



	int i=0;
	while (i < grid.size())
	{
		bool isColumnEmpty = false;
		if (grid[i].size() == 0)
		{
			grid.erase(grid.begin() + i);
			isColumnEmpty = true;
		}

		if (isColumnEmpty)
		{
			for (int j = i - 1; j >= 0; --j)
			{
				for (int k = 0; k < grid[j].size(); ++k)
				{
					grid[j][k]->boxrow = j;
					grid[j][k]->boxcolumn = k;
					grid[j][k]->setPosition(Vector2D(grid[j][k]->getPosition().x + boxSize + 1, grid[j][k]->getPosition().y));
				}
			}

			for (int j = i; j < grid.size(); ++j)
			{
				for (int k = 0; k < grid[j].size(); ++k)
				{
					grid[j][k]->boxrow = j;
					grid[j][k]->boxcolumn = k;
				}
			}
		}

		else if(grid[i].size() != 0 && !isColumnEmpty)
		{
			++i;
		}
		
	}
}