#include <SFML/Graphics.hpp>
#include <vector>



class GameStats{
public:
    explicit GameStats();
    void showMenu(sf::RenderWindow &window, int, int);

private:
    sf::Vector2f m_size;
    sf::Vector2f m_location;
    sf::RectangleShape m_shape;
    sf::Text m_clicks;
    sf::Text m_time;
};