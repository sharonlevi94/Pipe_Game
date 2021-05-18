#include "Controller.h"

Controller::Controller():
	m_window(sf::RenderWindow(sf::VideoMode(900, 700), "play_pipe")){}

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