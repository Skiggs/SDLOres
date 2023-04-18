#include"GameObject.h"
#include"TextureManager.h"

GameObject::GameObject(SDL_Renderer* ren)
{
}



Box::Box(const BoxColor boxNumber, int row, int column, const char* texture, SDL_Renderer* ren, std::function<void(int, int)> cb)
{
	renderer = ren;
	destRect.w = boxSize;
	destRect.h = boxSize;
	color = boxNumber;
	boxcolumn = column;
	boxrow = row;
	objTexture = TextureManager::LoadTexture(texture, renderer);
	callBack = cb;
}

void Box::update()
{
	checkIfMouseIsInside();
}

void Box::render()
{
	SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
}

bool Box::checkIfMouseIsInside()
{
	SDL_Point mouse;
	auto buttons = SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &destRect) && (buttons & SDL_BUTTON_LMASK))
	{
		callBack(boxrow, boxcolumn);
		return true;
	}

	return false;
}

ImageObj::ImageObj(const char* texture, SDL_Renderer* ren, int width, int height, Vector2D pos)
{
	renderer = ren;
	position = pos;
	destRect.w = width;
	destRect.h = height;
	destRect.x = pos.x;
	destRect.y = pos.y;
	objTexture = TextureManager::LoadTexture(texture, renderer);
}

void ImageObj::update()
{

}

void ImageObj::render()
{
	SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
}

bool ImageObj::checkIfMouseIsInside()
{
	SDL_Point mouse;
	auto buttons = SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &destRect) && (buttons & SDL_BUTTON_LMASK))
	{
		
		return true;
	}

	return false;
}