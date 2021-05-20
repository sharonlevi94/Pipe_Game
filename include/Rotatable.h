#pragma once
#include "Square.h"
#include "Directions.h"

class Rotatable : public Square {
public:
	Rotatable(const sf::Vector2f&, const sf::Vector2f&, char);
	void rotate();
private:
	struct Directions m_Directions;
};