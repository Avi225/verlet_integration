#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "aMath.hpp"

class aWindow
{
public:
	aWindow(const char* title, int width, int height);
	SDL_Texture* loadTexture(const char* filePath);

	int getRefreshRate();

	void cleanUp();

	void clear();

	void display();

	void aRenderFillCircle(vector2f position, int radius, SDL_Color color);
	void aRenderLine(vector2f positionA, vector2f positionB, SDL_Color color);
	void aRenderRectangle(SDL_Rect rect, SDL_Color color);
	void aRenderText(TTF_Font* font, vector2f position, const char* text, SDL_Color color);


private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	//SDL_Surface* textSurface;
	//SDL_Texture* textTexture;
};