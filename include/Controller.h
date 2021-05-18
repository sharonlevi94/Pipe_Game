#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"

class Controller {
public:
	Controller();
	void run();
	void draw();
private:
	sf::RenderWindow m_window;
	sf::RectangleShape m_background;
	int m_level;
	int m_matrixSize;
	//Board m_gameBoard;
	//State m_gameState;
	//sf::Clock m_gameClock;
	void levelUp();
	
};

