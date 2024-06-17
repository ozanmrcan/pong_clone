#include "Entity.h"

Entity::Entity(double x, double y, SDL_Texture* texture)
	:m_x{x}, m_y{y}, m_texture{texture}
{	
	m_currFrame.x = 0; m_currFrame.y = 0;
	SDL_QueryTexture(m_texture, NULL, NULL, &m_currFrame.w, &m_currFrame.h);
}

double Entity::getX() const { return m_x; }

double Entity::getY() const { return m_y; }

void Entity::setX(double in_x) { m_x = in_x; }

void Entity::setY(double in_y) { m_y = in_y; }

int Entity::getScore() const { return -1; }

SDL_Texture* Entity::getTexture() const { return m_texture; }

SDL_Rect Entity::getCurrFrame() const { return m_currFrame; }
