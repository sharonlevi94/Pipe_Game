#pragma once
#include <SFML/Graphics.hpp>
#include "Directions.h"

class Square {
public:
	Square(const sf::Vector2f&, const sf::Vector2f&, int);
	void draw(sf::RenderWindow&);
	sf::Sprite& getShape();
	//	const setShape(sf::Sprite&);
	void rotate();
	virtual ~Square() = default;
	void setNeighbours(std::vector<Square*>);
private:
	sf::Sprite m_shape;
	sf::Vector2f m_size;
	sf::Vector2f m_location;
	bool m_inSolution = false;
	Directions m_directions;
	//need to create data structure to hold 2 FULL/EMPTY sprites
	std::vector<Square*> m_neighbours;
};