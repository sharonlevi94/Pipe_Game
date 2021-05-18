#include "Rotatable.h"
#include "SFML/Graphics.hpp"

Rotatable::Rotatable(const sf::Vector2f& location, const sf::Vector2f& size, char type)
	:Square(location, size, type){}

void Rotatable::rotate() {
	sf::RectangleShape newShape = this->getShape();
	newShape.rotate(90.f);
	this->setShape(newShape);
}