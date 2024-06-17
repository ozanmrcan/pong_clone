#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"

class Player : public Entity
{
private:
	int m_score;
public:
	Player(double x, double y, SDL_Texture* texture);
	void move(double velocity, double deltaTime, const int SCREEN_HEIGHT);
	int getScore() const;
	void incrementScore();
};