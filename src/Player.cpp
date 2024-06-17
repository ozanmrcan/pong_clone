#include "Player.h"

Player::Player(double x, double y, SDL_Texture* texture)
	:Entity{ x, y, texture }, m_score{ 0 }
{ }

// up is positive, down is negative i.e. move(-10) moves down by 10 pixels
void Player::move(double velocity, double deltaTime, const int SCREEN_HEIGHT)
{	
	if (velocity > 0 && getY() >= 10 || velocity < 0 && getY() + getCurrFrame().h <= SCREEN_HEIGHT - 10)
		setY(getY() - velocity * 0.1 * deltaTime);
}

int Player::getScore() const
{
	return m_score;
}

void Player::incrementScore()
{
	m_score++;
}
