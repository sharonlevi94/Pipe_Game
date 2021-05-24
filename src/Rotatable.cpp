#include "Rotatable.h"

Rotatable::Rotatable(const sf::Vector2f& location, const sf::Vector2f& size, char type, bool water)
	:Square(location, size, type, water){}

void Rotatable::rotate() {
    getShape().rotate(90.f);
//	sf::Sprite newShape = this->getShape();
//	newShape.rotate(90.f);
//	this->setShape(newShape);
}