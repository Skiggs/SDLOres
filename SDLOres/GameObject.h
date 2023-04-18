#pragma once

#include"Game.h"
#include"Vector2D.h"
#include<functional>


class GameObject {

public:
	GameObject() = default;
	GameObject(SDL_Renderer* ren);
	~GameObject() {};

	virtual void update() = 0;
	virtual void render() = 0;
};


class ImageObj : public GameObject
{
public:
	ImageObj() = default;
	ImageObj(const char* texture, SDL_Renderer* ren, int height, int width, Vector2D pos);
	~ImageObj() { SDL_free(objTexture); };

	void update();
	void render();
	bool checkIfMouseIsInside();
	void setPosition(const Vector2D& vec)
	{
		position = vec;
		destRect.x = position.x;
		destRect.y = position.y;
	}
	Vector2D getPosition() const { return position; };
private:
	Vector2D position;
	SDL_Texture* objTexture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
};

enum class BoxColor
{
	BLUE = 1,
	GREEN = 2,
	ORANGE =3,
	RED = 4
};

const int boxSize = 50;

class Box :public GameObject
{
public:
	Box() = default;
	Box(const BoxColor boxNumber, int row, int column, const char* texture, SDL_Renderer* ren,std::function<void(int,int)> cb );
	~Box() { SDL_free(objTexture);  };

	void update();
	void render();
	void setPosition(const Vector2D& vec) 
	{
		position = vec;
		destRect.x = position.x;
		destRect.y = position.y;
	}
	Vector2D getPosition() const { return position; };
	bool checkIfMouseIsInside();
	BoxColor getColor() const { return color; }
	int boxrow, boxcolumn;
	bool isCollected = false;
private:
	std::function<void(const int, const int)> callBack;
	Vector2D position;
	SDL_Texture* objTexture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
	BoxColor color;	
};