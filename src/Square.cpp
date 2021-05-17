#include "Square.h"

Square::Square(const sf::Vector2f& size, const sf::Texture& texture, bool inSol)
	: m_size(size), m_texture(texture), m_inSolution(inSol) {}

void Square::draw(sf::RenderWindow& window) {
	window.draw(this->m_shape);
}