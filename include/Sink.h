#pragma once
#include "Square.h"
#include "Macros.h"

class Sink : public Square {
public:
	Sink(const sf::Vector2f&, const sf::Vector2f&, int, bool);
	int getDirection()const;
    void setDir(int);
private:
	int m_direction=UP;
};