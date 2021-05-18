#include "Controller.h"

Controller::Controller():
	m_window(sf::RenderWindow(sf::VideoMode(1200, 900), "play_pipe")), m_level(1),
	m_matrixSize(START_SIZE){
}

void Controller::run(){
    while (m_window.isOpen())
    {
        m_window.clear();
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

void Controller::levelUp() {
    if (m_level >= 8){
        if (m_level % 2 == 0)   m_matrixSize++;
    }
}