#include "Square.h"
#include "Resources.h"
#include "Macros.h"

Square::Square(const sf::Vector2f& location,
	const sf::Vector2f& size, int type)
	: m_location(location), m_size(size) {
	m_neighbours = {};
	m_shape.setPosition(location);
	m_shape.setTexture(Resources::instance().getTexture(type));
	this->m_shape.setOrigin(sf::Vector2f{ (m_shape.getTexture()->getSize().x / 2.f),
		(m_shape.getTexture()->getSize().y / 2.f) });
	switch (type) {
	case STRAIGHT_PIPE:
		m_directions.
	}
}

void Square::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

sf::Sprite& Square::getShape() {
	return this->m_shape;
}

void Square::rotate() {
	m_shape.rotate(90.f);
}