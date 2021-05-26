#include "Controller.h"
#include "Resources.h"
#include "Macros.h"
#include "Rotatable.h"


//============================================================================
Controller::Controller():
        m_window(sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "play_pipe")), m_level(1),
        m_matrixSize(LEVEL_SIZE),
        m_background(sf::RectangleShape()),
        m_gameStats(),
        m_clicks(0),
        m_board(Board(sf::Vector2f(576, 100), sf::Vector2f(BOARD_SIZE, BOARD_SIZE))){
    this->m_background.setSize(sf::Vector2f(m_window.getSize()));
    this->m_background.setPosition(sf::Vector2f(0, 0));
    this->m_background.setTexture(&Resources::instance().getBackground());

}
//============================================================================
void Controller::run(){
    m_board.loadNewLevel();
    //start clock
    m_gameClock.restart();
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

                if(this->m_board.getContent(sf::Vector2f((float)event.mouseButton.x,(float)event.mouseButton.y)) != nullptr)
                    if(dynamic_cast<Rotatable*>(this->m_board.getContent(sf::Vector2f((float)event.mouseButton.x,(float)event.mouseButton.y)))) {
                        this->m_board.getContent(
                                sf::Vector2f((float) event.mouseButton.x, (float) event.mouseButton.y))->rotate();
                        m_clicks++;
                    }
                break;
            default:
                    ; // to avoid 22 enums warning in switch
            }
            // next level
            if (m_board.getWaterInSink())   m_board.loadNewLevel();
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
    m_gameStats.showMenu(m_window, m_clicks, int(m_gameClock.getElapsedTime().asSeconds()));
}