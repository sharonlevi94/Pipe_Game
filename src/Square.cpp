#include "Square.h"
#include "Resources.h"

Square::Square(const sf::Vector2f& location,
	const sf::Vector2f& size, int type)
	: m_location(location),m_size(size) {
	//m_neighbours = {};
	m_shape.setTexture(Resources::instance().getTexture(type));
	m_shape.setOrigin(m_shape.getGlobalBounds().width / 2, m_shape.getGlobalBounds().height / 2);
	m_shape.setPosition(location);
}

void Square::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

sf::Sprite &Square:: getShape() {
	return this->m_shape;
}

//void Square::setShape(sf::Sprite& shape) {
//	m_shape(shape);
//}

void Square::rotate() {
	m_shape.rotate(90.f);
}