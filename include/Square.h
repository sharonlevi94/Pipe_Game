#pragma once
#include <SFML/Graphics.hpp>

class Square {
public:
	Square(const sf::Vector2f&, const sf::Texture&, bool);
	void draw(sf::RenderWindow&);
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_size;
	sf::Vector2f m_location;
	sf::Texture m_texture;
	bool m_inSolution = false;
	std::vector<Square*> m_neighbours;
};