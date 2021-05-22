#pragma once
//============================ include section ===============================
#include <SFML/Graphics.hpp>
#include "Directions.h"

class Square {
public:
	Square(const sf::Vector2f&, const sf::Vector2f&, int);
	virtual ~Square() = default;

	void draw(sf::RenderWindow&);
	sf::Sprite& getShape();
	void rotate();
	void setNeighbours(std::vector<Square*>);
	void setDirections(bool, bool, bool, bool);
private:
	sf::Sprite m_shape;
	sf::Vector2f m_size;
	sf::Vector2f m_location;
	Directions m_directions;
	std::vector<Square*> m_neighbours;
};