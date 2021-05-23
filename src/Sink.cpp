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
		m_direction = DOWN;
		break;
	case LEFT:
		this->rotate(); this->rotate(); this->rotate();
		setDirections(false, false, true, false);
		m_direction = LEFT;
		break;
	case RIGHT:
		this->rotate();
		setDirections(false, false, false, true);
		m_direction = RIGHT;
		break;
	default:
		break;
	}
}

int Sink::getDirection()const {
	return m_direction;
}