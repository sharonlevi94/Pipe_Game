#include "Sink.h"
#include "Resources.h"
#include "Macros.h"

Sink::Sink(const sf::Vector2f& location,
	const sf::Vector2f& size, int type, char direction)
	: Square(location, size, type) {
    this->getShape().setTexture(Resources::instance().getTexture(type));
    this->getShape().setOrigin(this->getShape().getGlobalBounds().width / 2,
                               this->getShape().getGlobalBounds().height / 2);
    this->getShape().setPosition(location);
}