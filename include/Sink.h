#pragma once
#include "Square.h"
#include "Macros.h"

class Sink : public Square {
public:
	Sink(const sf::Vector2f&, const sf::Vector2f&, int);
	int getDirection()const;
private:
	int m_direction=UP;
};