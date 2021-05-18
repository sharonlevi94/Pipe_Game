#include "Controller.h"
#include "Resources.h"
//============================================================================
Controller::Controller():
	m_window(sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "play_pipe")), m_level(1),
	m_matrixSize(START_SIZE),
    m_background(sf::RectangleShape()){
    this->m_background.setSize(sf::Vector2f(m_window.getSize()));
    this->m_background.setPosition(sf::Vector2f(0, 0));
    this->m_background.setTexture(&Resources::instance().getBackground());
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
}