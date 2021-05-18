#pragma once
#include <SFML/Graphics.hpp>

class Controller {
public:
	Controller();
	void run();
private:
	sf::RenderWindow m_window;
	//Board m_gameBoard;
	//State m_gameState;
	//sf::Clock m_gameClock;
};