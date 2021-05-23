#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GameStats.h"

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
	Board m_board;
	GameStats m_gameStats;
	int m_clicks;

//	State m_gameState;
	sf::Clock m_gameClock;
	void levelUp();
};

