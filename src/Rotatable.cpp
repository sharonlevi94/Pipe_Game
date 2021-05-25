#include "Rotatable.h"

Rotatable::Rotatable(const sf::Vector2f& location, const sf::Vector2f& size, int empty, int full, bool water)
	:Square(location, size, empty, full, water){}

void Rotatable::rotate() {
    getShape().rotate(90.f);
//	sf::Sprite newShape = this->getShape();
//	newShape.rotate(90.f);
//	this->setShape(newShape);
}