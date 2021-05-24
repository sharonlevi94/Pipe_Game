#pragma once
#include "Square.h"

class Rotatable : public Square {
public:
	Rotatable(const sf::Vector2f&, const sf::Vector2f&, char, bool);
	void rotate();
private:
};