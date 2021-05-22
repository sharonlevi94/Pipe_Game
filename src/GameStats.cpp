#include "GameStats.h"
#include "Macros.h"
#include "Resources.h"
#include <string>

GameStats::GameStats() {
    auto* gameFont = new sf::Font();
    gameFont->loadFromFile("C:/Windows/Fonts/Arial.ttf");
    m_shape.setSize(sf::Vector2f{300, 400});
    m_shape.setPosition(1460, 250);
    m_shape.setFillColor(sf::Color(50, 50, 50, 150));
    m_clicks.setFont(*gameFont);
    m_clicks.setString('0');
    m_clicks.setPosition(1550, 600);
    m_time.setFont(*gameFont);
    m_time.setString('0');
    m_time.setPosition(1550, 400);

}
void GameStats::showMenu(sf::RenderWindow &window, int clicks, int gameTime) {
    m_clicks.setString("Clicks:   " + std::to_string(clicks));
    m_time.setString("Time:   " + std::to_string((gameTime)));
    window.draw(m_shape);
    window.draw(m_clicks);
    window.draw(m_time);
    window.display();
}