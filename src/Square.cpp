#include "Square.h"
#include "Resources.h"
#include "Macros.h"

Square::Square(const sf::Vector2f& location,
	const sf::Vector2f& size, int type, bool water)
	: m_location(location), m_size(size), m_runningWater(water) {
	m_neighbours = {};
	m_shape.setPosition(location);
	m_shape.setTexture(Resources::instance().getTexture(type));
	this->m_shape.setOrigin(sf::Vector2f{ (m_shape.getTexture()->getSize().x / 2.f),
		(m_shape.getTexture()->getSize().y / 2.f) });
	switch (type) {
        case STRAIGHT_PIPE_E:
            setDirections(true, true, false, false);
            break;
        case T_PIPE_E:
            setDirections(true, true, true, false);
            break;
        case PLUS_PIPE_E:
            setDirections(true, true, true, true);
            break;
        case CORNER_PIPE_E:
            setDirections(true, false, true, false);
            break;
        case FAUCET_F:
            setDirections(true, false, false, false);
            break;
        case SINK_E:
            setDirections(true, false, false, false);

		default:
            break;
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

void Square::setNeighbours(std::vector<Square*> neighbours) {
	for (auto& neighbour : neighbours) 
		this->m_neighbours.push_back(neighbour);
}

void Square::setDirections(bool up, bool down, bool left, bool right) {
	m_directions.m_up = up;
	m_directions.m_down = down;
	m_directions.m_left = left;
	m_directions.m_right = right;
}

Directions Square::getDirections() {
    return m_directions;
}

bool Square::getRunningWater() {
    return m_runningWater;
}

void Square::setRunningWater(bool isRunning) {
    m_runningWater = isRunning;
}