#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <random>

#include "Entity.h"
#include "Player.h"

struct Velocity {
	double xVel, yVel;
};

class Ball : public Entity
{
private:
	double m_velX, m_velY;
public:
	Ball(double x, double y, SDL_Texture* texture, double velX, double velY);
	double getVelX() const;
	double getVelY() const;
	void setVelX(double velX);
	void setVelY(double velY);
	int move(double deltaTime, Player& rPlayer, Player& lPlayer, const int SCREEN_HEIGHT,const int SCREEN_WIDTH);
	double randomVelocity();
	void setRandomVelocity(int direction, const double BASE_BALL_VELX);
	void resetPosition(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
};