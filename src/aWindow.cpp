#include <aWindow.hpp>


aWindow::aWindow(const char* title, int width, int height)
	: window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "window init failed. Error: " <<  SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* aWindow::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL)
		std::cout << "texture loading failed. Error: " <<  SDL_GetError() << std::endl;
	return texture;
}

int aWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void aWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void aWindow::clear()
{
	SDL_RenderClear(renderer);
}

void aWindow::display()
{
	SDL_RenderPresent(renderer);
}

void aWindow::aRenderFillCircle(vector2f position, int radius, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int offsetx, offsety, d;
	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx) {

		SDL_RenderDrawLine(renderer, position.x - offsety, position.y + offsetx, position.x + offsety, position.y + offsetx);
		SDL_RenderDrawLine(renderer, position.x - offsetx, position.y + offsety, position.x + offsetx, position.y + offsety);
		SDL_RenderDrawLine(renderer, position.x - offsetx, position.y - offsety, position.x + offsetx, position.y - offsety);
		SDL_RenderDrawLine(renderer, position.x - offsety, position.y - offsetx, position.x + offsety, position.y - offsetx);

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void aWindow::aRenderLine(vector2f positionA, vector2f positionB, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(renderer, positionA.x, positionA.y, positionB.x, positionB.y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void aWindow::aRenderRectangle(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void aWindow::aRenderText(TTF_Font* font, vector2f position, const char* text, SDL_Color color)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect rect = {int(position.x), int(position.y), textSurface->w, textSurface->h};

	SDL_RenderCopy(renderer, textTexture, NULL, &rect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

