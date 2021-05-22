#include "Sink.h"
#include "Resources.h"
#include "Macros.h"

Sink::Sink(const sf::Vector2f& location,
	const sf::Vector2f& size, int type)
	: Square(location, size, type) {
	this->getShape().setTexture(Resources::instance().getTexture(type));
	this->getShape().setOrigin(this->getShape().getGlobalBounds().width / 2,
		this->getShape().getGlobalBounds().height / 2);
	this->getShape().setPosition(location);
	int randDirection = std::rand() % DIRECTIONS_NUM;
	switch (randDirection) {
	case DOWN:
		this->rotate(); this->rotate();
		setDirections(false, true, false, false);
		break;
	case LEFT:
		this->rotate(); this->rotate(); this->rotate();
		setDirections(false, false, true, false);
		break;
	case RIGHT:
		this->rotate();
		setDirections(false, false, false, true);
		break;
	default:
		break;
	}
}