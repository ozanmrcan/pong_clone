#include "RenderWindow.h"
#include <iostream>

RenderWindow::RenderWindow(const char* title, int width, int height)
	:m_window{NULL}, m_renderer{NULL}
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		
	if (m_window == NULL)
		std::cout << "SDL_CreateWindow failed, SDL_Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL)
		std::cout << "SDL_CreateRenderer failed, SDL_Error: " << SDL_GetError() << std::endl;

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char* path)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(m_renderer, path);
	if (texture == NULL)
		std::cout << "IMG_LoadTexture failed, SDL_Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::clear()
{
	SDL_RenderClear(m_renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(m_renderer);
}

void RenderWindow::render(Entity& entity)
{
	SDL_Rect src = entity.getCurrFrame();

	SDL_Rect dst = { (int)entity.getX(), (int)entity.getY(), entity.getCurrFrame().w, entity.getCurrFrame().h};

	SDL_RenderCopy(m_renderer, entity.getTexture(), &src, &dst);
}

void RenderWindow::renderingCycle(Entity& line1, Entity& line2, Entity& line3, Entity& b, Entity& r, Entity& l, TTF_Font* font, const int SCREEN_WIDTH)
{
	SDL_RenderClear(m_renderer);
	render(line1); render(line2); render(line3);
	render(b); render(r); render(l);
	renderText(font, "PONG", SCREEN_WIDTH/2, 50, 200, 70);
	renderText(font, std::to_string(l.getScore()), 200, 100, 50, 50);
	renderText(font, std::to_string(r.getScore()), SCREEN_WIDTH - 250, 100, 50, 50);
	SDL_RenderPresent(m_renderer);
}

void RenderWindow::renderText(TTF_Font* font, std::string str, int x, int y, int w, int h)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, str.c_str(), { 255, 255, 255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);	
	
	std::cout << SDL_GetError();

	SDL_Rect src = { 0, 0, textSurface->w, textSurface->h };
	SDL_Rect dst = { x - w/2, y, w, h };

	SDL_RenderCopy(m_renderer, textTexture, &src, &dst);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}



