#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

#include "Entity.h"
#include "Player.h"

class RenderWindow
{
public:
	RenderWindow(const char* title, int width, int height);
	void cleanUp();
	SDL_Texture* loadTexture(const char* path);
	void clear();
	void display();
	void render(Entity& entity);
	void renderingCycle(Entity&, Entity&, Entity&, Entity&, Entity&, Entity&, TTF_Font* font, const int SCREEN_WIDTH);
	void renderText(TTF_Font* font, std::string str, int x, int y, int w, int h);
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};