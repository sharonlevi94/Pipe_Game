#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"

class Controller {
public:
	Controller();
	void run();

private:
	sf::RenderWindow m_window;
	int m_level;
	int m_matrixSize;
	//Board m_gameBoard;
	//State m_gameState;
	//sf::Clock m_gameClock;
	void levelUp();
};

