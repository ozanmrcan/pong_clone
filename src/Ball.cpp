#include "Ball.h"
#include <iostream>
#include <math.h>

Ball::Ball(double x, double y, SDL_Texture* texture, double velX, double velY)
	:Entity{ x, y, texture }, m_velX{ velX }, m_velY{ velY }
{ }

double Ball::getVelX() const { return m_velX; }

double Ball::getVelY() const { return m_velY; }

void Ball::setVelX(double velX) { m_velX = velX; }

void Ball::setVelY(double velY) { m_velY = velY; }

// returns 0 normally, return 1 if right scores, returns -1 if left scores
int Ball::move(double deltaTime, Player& rPlayer, Player& lPlayer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
	double baseVelX = m_velX;
	setX(getX() - m_velX * 0.1 * deltaTime);
	setY(getY() - m_velY * 0.1 * deltaTime);

	// ball - player collision
	if (this->getX() + this->getCurrFrame().w >= rPlayer.getX() + 10  // x axis for right player
		&& this->getY() >= rPlayer.getY() && this->getY() <= rPlayer.getY() + rPlayer.getCurrFrame().h) // y axis for right player
	{
		double newVelY = 5 * ((rPlayer.getY() + rPlayer.getCurrFrame().h / 2.0) - (this->getY() + this->getCurrFrame().h / 2)) / (rPlayer.getCurrFrame().h / 2);
		setVelY(newVelY);
		setVelX(-getVelX() * 1.1); // increasing velocity at each hit
	}
	else if (this->getX() <= lPlayer.getX() + rPlayer.getCurrFrame().w - 10 // x axis for left player
		&& this->getY() >= lPlayer.getY() && this->getY() <= lPlayer.getY() + rPlayer.getCurrFrame().h) // y axis for left player
	{
		double newVelY = 5 * ((lPlayer.getY() + lPlayer.getCurrFrame().h / 2.0) - (this->getY() + this->getCurrFrame().h / 2)) / (lPlayer.getCurrFrame().h / 2);
		setVelY(newVelY);
		setVelX(-getVelX() * 1.1); // increasing velocity at each hit
	}

	// ball - upper bounds collision
	if (this->getY() <= 0 || this->getY() >= SCREEN_HEIGHT - this->getCurrFrame().h)
	{
		setVelY(-getVelY());	
	}

	// score collision
	if (this->getX() + this->getCurrFrame().w / 2.0 <= lPlayer.getX() + lPlayer.getCurrFrame().w / 2.0) // right player scores
	{
		rPlayer.incrementScore();
		return 1;
	}
	else if (this->getX() + this->getCurrFrame().w / 2.0 >= rPlayer.getX() + rPlayer.getCurrFrame().w / 2.0) // left player scores
	{
		lPlayer.incrementScore();
		return -1;
	}
	return 0;
}

double Ball::randomVelocity()
{
	std::random_device rd;
	std::uniform_real_distribution<double> dist(-4, 4);
	return dist(rd);
}

// if direction is 1, goes to right, else goes to left
void Ball::setRandomVelocity(int direction, const double BASE_BALL_VELX)
{
	setVelX(direction * BASE_BALL_VELX);
	setVelY(randomVelocity());
}

void Ball::resetPosition(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	setY(SCREEN_WIDTH / 2 - 16);
	setX(SCREEN_HEIGHT / 2 - 16);
}
