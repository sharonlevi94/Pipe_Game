//============================= include section ==========================
#include "Board.h"
#include "Sink.h"
#include "Macros.h"
#include "Resources.h"
#include <vector>
#include "Rotatable.h"
#include <ctime>
using std::vector;
//====================== Constructors & distructors section ==================
Board::Board(const sf::Vector2f& location,
             const sf::Vector2f& size)
        :/* m_levelReader(DataReader()),*/
          m_location(location),
        m_size(size) {
        m_sinks = {};     
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
void Board::loadNewLevel() {
        sf::Vector2f boxSize(BOX_WIDTH, BOX_HEIGHT);
        
        this->InitializeMap();
        this->m_faucetLoc = this->setFaucet(boxSize);
        this->setSinks(boxSize);
        this->buildRoutes(); //Bonus +4 pts
        
        //reset last load parameters:
        this->releaseMap();
        this->m_map.resize(LEVEL_SIZE);
        std::srand(time(0));
        int randVal = (std::rand() % (20 - 10 + 1) / 2) * 2 + 10;

        //allocating level's objects:
        for (int y = 0; y < LEVEL_SIZE; ++y) {
            for (int x = 0; x < LEVEL_SIZE; x++) {
                randVal = (rand() % (20 - 10 + 1) / 2) * 2 + 10;
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

                default:
                    this->m_map[y].push_back(nullptr); // ' ' inserted
                    break;

                }
            }
        }
        this->calcNeighbours(); //Bonus +2 pts
        
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
    //run on the internal DB
std:vector<Square*> neighbours = {};
    for (int row = 0; row < m_map.size(); row++) {
        neighbours.clear();
        for (int col = 0; col < m_map.size(); col++) {
            neighbours.clear();
            if (row > 0)
                neighbours.push_back(m_map[row - 1][col].get()); //up
            else
                neighbours.push_back(nullptr);
            if (row < m_map.size() - 1)
                neighbours.push_back(m_map[row + 1][col].get()); //down
            else
                neighbours.push_back(nullptr);
            if (col > 0)
                neighbours.push_back(m_map[row][col - 1].get()); //left
            else
                neighbours.push_back(nullptr);
            if (col < m_map.size() - 1)
                neighbours.push_back(m_map[row][col + 1].get()); //right
            else
                neighbours.push_back(nullptr);

            m_map[row][col]->setNeighbours(neighbours);
        }
    }
}
//============================== private section =============================
void Board::releaseMap() {
    this->m_map.clear();
}
//============================================================================
void Board::setSinks(sf::Vector2f boxSize) {
    for (int sink = 0; sink <= 2; sink++) {
        int randRow = std::rand() % BOARD_SIZE;
        int randCol = std::rand() % BOARD_SIZE;
        while (m_map[randRow][randCol].get() != nullptr) { //find empty place for new sink
            int randRow = std::rand() % BOARD_SIZE;
            int randCol = std::rand() % BOARD_SIZE;
        }
        this->m_map[randRow].push_back(std::make_unique <Square>(sf::Vector2f
        (boxSize.x * randCol + 64, boxSize.y * randRow + 64) + this->m_location, boxSize, FAUCET_F));
        //save the place of the sink in the DB:
        m_sinks.push_back(sf::Vector2f(randRow, randCol));
    }
}
//============================================================================
sf::Vector2f Board::setFaucet(sf::Vector2f boxSize) {
        int randRow = std::rand() % BOARD_SIZE;
        int randCol = std::rand() % BOARD_SIZE;
        while (m_map[randRow][randCol].get() != nullptr) { 
            int randRow = std::rand() % BOARD_SIZE;
            int randCol = std::rand() % BOARD_SIZE;
        }
        this->m_map[randRow][randCol] = std::make_unique <Rotatable>(sf::Vector2f
        (boxSize.x * randCol + 64, boxSize.y * randRow + 64) + this->m_location, boxSize, SINK_E);

        return sf::Vector2f(randRow, randCol);
}
//============================================================================
void Board::InitializeMap() {
    for(int row =0 ; row<BOARD_SIZE ; row++)
        for (int col = 0; col < BOARD_SIZE; col++) 
            m_map[row].push_back(nullptr);
}
//============================================================================
std::vector<sf::Vector2f> Board::rafflePoints() {
    std::vector<sf::Vector2f> points = {};
    for (int point =0; point < ROUTE_POINTS; point++) {
        int randRow = std::rand() % BOARD_SIZE;
        int randCol = std::rand() % BOARD_SIZE;
        while (m_map[randRow][randCol].get() != nullptr) { //find empty place for new sink
            int randRow = std::rand() % BOARD_SIZE;
            int randCol = std::rand() % BOARD_SIZE;
        }
        points.push_back(sf::Vector2f(randRow, randCol));
    }
    return points;
}
//============================================================================
void Board::buildRoutePoint2Point(sf::Vector2f start, sf::Vector2f end) {
    sf::Vector2f boxSize(BOX_WIDTH, BOX_HEIGHT);
    while (start != end) {
        if (start.x != end.x) { //diff cols
            if (end.y == start.y) { //same rows
                if (end.x > start.x) { //end is right to start

                    this->m_map[start.y][start.x + 1] = std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * (start.x + 1) + 64, boxSize.y * start.y + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E);
                    start.x++;
                }
                else {//end is left to start
                    this->m_map[start.y][start.x - 1] = std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * (start.x - 1) + 64, boxSize.y * start.y + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E);
                    start.x--;
                }
            }
            else { //diff rows
                if (end.x > start.x) {
                    if (end.y < start.y) { //case above & right
                        this->m_map[start.y][start.x + 1] = std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * (start.x + 1) + 64, boxSize.y * start.y + 64) + this->m_location, boxSize, CORNER_PIPE_E);
                        start.x++;
                    }
                }
                else {
                    if (end.y < start.y) { //case above & left
                        this->m_map[start.y][start.x - 1] = std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * (start.x - 1) + 64, boxSize.y * start.y + 64) + this->m_location, boxSize, CORNER_PIPE_E);
                        start.x--;
                    }
                }
            }
        }
        else { //same cols
            if (end.y < start.y) { // end above to start
                this->m_map[start.y + 1][start.x] = std::make_unique <Rotatable>(sf::Vector2f
                (boxSize.x * (start.x) + 64, boxSize.y * (start.y + 1) + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E);
                start.y++;
            }
            else {
                this->m_map[start.y - 1][start.x] = std::make_unique <Rotatable>(sf::Vector2f
                (boxSize.x * (start.x) + 64, boxSize.y * (start.y - 1) + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E);
                start.y--;
            }
        }
    }
    if (end != m_faucetLoc) {
        this->m_map[start.y][start.x] = std::make_unique <Rotatable>(sf::Vector2f
        (boxSize.x * (start.x) + 64, boxSize.y * (start.y) + 64) + this->m_location, boxSize, PLUS_PIPE_E);
    }
}
//============================================================================
void Board::buildRoutes() {
    for (auto& sink: m_sinks) {
        std::vector<sf::Vector2f> routePoints = this->rafflePoints();
            buildRoutePoint2Point(sink, routePoints[0]);
            buildRoutePoint2Point(routePoints[0], routePoints[1]);
            buildRoutePoint2Point(routePoints[1],m_faucetLoc);
    }
}
