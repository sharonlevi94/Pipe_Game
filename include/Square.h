#pragma once
#include <SFML/Graphics.hpp>

class Square {
public:
	Square(const sf::Vector2f& , const sf::Vector2f&, int);
	void draw(sf::RenderWindow&);
	sf::Sprite &getShape();
//	const setShape(sf::Sprite&);
	void rotate();

private:
	sf::Sprite m_shape;
	sf::Vector2f m_size;
	sf::Vector2f m_location;
	bool m_inSolution = false;
	//need to create data structure to hold 2 FULL/EMPTY sprites
	//std::vector<std::unique_ptr<Square>> m_neighbours;
};