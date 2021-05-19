#include "Square.h"
#include "Resources.h"

Square::Square(const sf::Vector2f& location,
	const sf::Vector2f& size, char type)
	: m_location(location),m_size(size) {
	//m_neighbours = {};
	m_shape.setTexture(&Resources::instance()
		.getTexture(type));
}

void Square::draw(sf::RenderWindow& window) {
	window.draw(this->m_shape);
}

sf::RectangleShape Square::getShape()const {
	return this->m_shape;
}

void Square::setShape(sf::RectangleShape& shape) {
	this->m_shape = shape;
}