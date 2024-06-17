#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Entity 
{
private:
	double m_x, m_y;
	SDL_Texture* m_texture;
	SDL_Rect m_currFrame;
public:
	Entity(double x, double y, SDL_Texture* texture);
	double getX() const;
	double getY() const;
	void setX(double in_x);
	void setY(double in_y);
	virtual int getScore() const;
	SDL_Texture* getTexture() const;
	SDL_Rect getCurrFrame() const;
};