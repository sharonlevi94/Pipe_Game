#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Square {
public:
	Square(const sf::Vector2f& , const sf::Vector2f&, char);
	void draw(sf::RenderWindow&);
	sf::RectangleShape getShape()const;
	void setShape(sf::RectangleShape&);
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_size;
	sf::Vector2f m_location;
	bool m_inSolution = false;
	//std::vector<std::unique_ptr<Square>> m_neighbours;
};