//============================= include section ==========================
#include "Board.h"
#include "Sink.h"
#include "Macros.h"
#include "Resources.h"
#include <vector>
#include "Rotatable.h"

using std::vector;
//====================== Constructors & distructors section ==================
Board::Board(const sf::Vector2f& location,
             const sf::Vector2f& size)
        :/* m_levelReader(DataReader()),*/
          m_location(location),
        m_size(size) {
        m_faucets = {};
}
//================================ gets section ==============================
Square* Board::getContent(const sf::Vector2f& location) {
    if (location.x >= m_location.x && location.x <= m_location.x + m_size.x)
        if (location.y >= m_location.y && location.y <= m_location.y + m_size.y) {
            int x = (int)((location.x - this->m_location.x)) / SQUARE_LEN ,
                y = (int)((location.y - this->m_location.y)) / SQUARE_LEN ;


            if ((Rotatable*)(this->m_map[y][x].get()))
                return ((Rotatable*)this->m_map[y][x].get());
        }
    return nullptr;
}
//============================ methods section ===============================
void Board::draw(sf::RenderWindow& window){
    for (int i = 0; i < this->m_map.size(); i++)
        for (int j = 0; j < this->m_map[i].size(); j++)
            if (m_map[i][j].get() != nullptr) {
                m_map[i][j]->draw(window);
             
            }
}
//============================================================================
/* 
 * This function update the objects of the game to the current level game.
 * the function build a vector of moving objects ptrs & return it.
 */
vector<Rotatable*> Board::loadNewLevel() {
        vector<Rotatable*> faucetVec = {};
        sf::Vector2f boxSize(128, 128);
        //reset last load parameters:
        this->releaseMap();
        this->m_map.resize(LEVEL_SIZE);
        int randVal = (std::rand() % (20 - 10 + 1) / 2) * 2 + 10;
        //allocating level's objects:
        for (int y = 0; y < LEVEL_SIZE; ++y) {
            for (int x = 0; x < LEVEL_SIZE; x++) {
                randVal = (std::rand() % (20 - 10 + 1) / 2) * 2 + 10;
                switch (randVal)
                {
                case STRAIGHT_PIPE_E:
                    this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * x + 64, boxSize.y * y + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E));
                    break;
                case T_PIPE_E:
                    this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * x + 64, boxSize.y * y + 64) + this->m_location, boxSize, T_PIPE_E));
                    break;
                case PLUS_PIPE_E:
                    this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * x + 64, boxSize.y * y + 64) + this->m_location, boxSize, PLUS_PIPE_E));
                    break;
                case CORNER_PIPE_E:
                    this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * x + 64, boxSize.y * y + 64) + this->m_location, boxSize, CORNER_PIPE_E));
                    break;
                case SINK_E:
                    this->m_map[y].push_back(std::make_unique <Sink>(sf::Vector2f
                    (boxSize.x * x + 64, boxSize.y * y + 64) + this->m_location, boxSize, SINK_E, SINK_E));
                    break;
                case FAUCET_F:
                    this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * x + 64, boxSize.y * y + 64) + this->m_location, boxSize, FAUCET_F));
                    faucetVec.push_back((Rotatable*)this->m_map[y][x].get());
                    break;
                default:
                    this->m_map[y].push_back(nullptr); // ' ' inserted
                    break;

                }
            }
        }
        return faucetVec;
}
//============================================================================
/*
* This function load the background and the music of the current level.
*/
void Board::loadLevelEffects() {
    //Resources::instance().playMusic();
}
//============================================================================
void Board::calcNeighbours() {
    this->calcInernalNeighbours();
    //run on the external cols of the DB:
    this->calcFirstColNeighbours();
    this->calcLastColNeighbours();
}
//============================== private section =============================
void Board::releaseMap() {
    this->m_map.clear();
}
//============================================================================
void Board::calcInernalNeighbours() {
    //run on the internal DB
    for (int row = 0; row < m_size.y; row++) {
    std:vector<Square*> neighbours = {};
        for (int col = 1; col < m_size.x - 1; col++) {
            if (row > 0)
                neighbours.push_back(m_map[row - 1][col].get()); //up
            else
                neighbours.push_back(nullptr);
            if (row < m_size.y - 1)
                neighbours.push_back(m_map[row + 1][col].get()); //down
            else
                neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row][col - 1].get()); //left
            neighbours.push_back(m_map[row][col + 1].get()); //right
            m_map[row][col]->setNeighbours(neighbours);
        }
    }
}
//============================================================================
void Board::calcFirstColNeighbours() {
    //first col
    for (int row = 0; row < m_size.x; row++) {
    std:vector<Square*> neighbours = {};
        if (row == 0) { //top left
            neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row + 1][0].get());
            neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row][1].get());
            m_map[row][0]->setNeighbours(neighbours);
        }
        if (row == m_size.x - 1) { //bottom left
            neighbours.push_back(m_map[row - 1][0].get());
            neighbours.push_back(nullptr);
            neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row][1].get());
            m_map[row][0]->setNeighbours(neighbours);
        }
        else {
            neighbours.push_back(m_map[row - 1][0].get());
            neighbours.push_back(m_map[row + 1][0].get());
            neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row][1].get());
            m_map[row][0]->setNeighbours(neighbours);
        }
    }
}
//============================================================================
void Board::calcLastColNeighbours() {
    //last col
    for (int row = 0; row < m_size.x; row++) {
    std:vector<Square*> neighbours = {};
        if (row == 0) { //top right
            neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row + 1][m_size.x].get());
            neighbours.push_back(m_map[row][m_size.x - 2].get());
            neighbours.push_back(nullptr);
            m_map[row][0]->setNeighbours(neighbours);
        }
        if (row == m_size.x - 1) { //bottom right
            neighbours.push_back(m_map[row - 1][m_size.x].get());
            neighbours.push_back(nullptr);
            neighbours.push_back(m_map[row][m_size.x - 2].get());
            neighbours.push_back(nullptr);
            m_map[row][0]->setNeighbours(neighbours);
        }
        else {
            neighbours.push_back(m_map[row - 1][m_size.x].get());
            neighbours.push_back(m_map[row + 1][m_size.x].get());
            neighbours.push_back(m_map[row][m_size.x - 2].get());
            neighbours.push_back(nullptr);
            m_map[row][0]->setNeighbours(neighbours);
        }
    }
}