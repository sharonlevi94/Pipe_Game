#include "Controller.h"
#include "Resources.h"
#include "Macros.h"

//============================================================================
Controller::Controller():
	m_window(sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "play_pipe")), m_level(1),
	m_matrixSize(START_SIZE),
    m_board(sf::Vector2f(640,160), sf::Vector2f(800, 800)){
//    this->m_background.setSize(sf::Vector2f(m_window.getSize()));
    this->m_background.setPosition(sf::Vector2f(0, 0));
//    this->m_background.setTexture(&Resources::instance().getBackground());
    auto* texture = new sf::Texture;		//texture for the background
    texture->loadFromFile("Background.png");
    m_background = sf::RectangleShape(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
    m_background.setTexture(texture);
    m_board.loadNewLevel();

}
//============================================================================
void Controller::run(){
    while (m_window.isOpen())
    {
        m_window.clear();
        this->draw();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                    ; // to avoid 22 enums warning in switch
            }


        }
    }
}
//============================================================================
void Controller::levelUp() {
    if (m_level >= 8){
        if (m_level % 2 == 0)   m_matrixSize++;
    }
}
//============================================================================
void Controller::draw() {
    m_window.draw(m_background);
    m_board.draw(m_window);
}