//============================= include section ==========================
#include "Board.h"
#include "Macros.h"
#include "Resources.h"
#include <vector>
#include "Rotatable.h"
#include "Sink.h"
#include <ctime>
using std::vector;
//====================== Constructors & distructors section ==================
Board::Board(const sf::Vector2f& location,
             const sf::Vector2f& size):
          m_location(location),
        m_size(size) {
        m_solved = false;
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
void Board::draw(sf::RenderWindow &window) {

    this->runEvenMoreWater(this->m_faucetLoc.x, this->m_faucetLoc.y, 0);
    this->runWater();
    for (int i = 0; i < this->m_map.size(); i++) {
        for (int j = 0; j < this->m_map[i].size(); j++) {
            if (m_map[i][j].get() != nullptr) {
                m_map[i][j]->draw(window);
            }
        }
    }
    for (int i = 0; i < LEVEL_SIZE; ++i) {
        for (int j = 0; j < LEVEL_SIZE; ++j) {
            if (sf::Vector2f(i, j) == m_faucetLoc or sf::Vector2f(i, j) == m_sinkLoc)  continue;
            m_map[i][j].get()->setRunningWater(false);
        }
    }
}
//============================================================================
/* 
 * This function update the objects of the game to the current level game.
 * the function build a vector of moving objects ptrs & return it.
 */
void Board::loadNewLevel() {
    m_solved = false;
        sf::Vector2f boxSize(BOX_WIDTH, BOX_HEIGHT);
        
        //reset last load parameters:
        this->releaseMap();
        this->m_map.resize(LEVEL_SIZE);
        std::srand(time(0));
        int randVal = (std::rand() % (20 - 10 + 1) / 2) * 2 + 10;

        this->InitializeMap();
        this->m_faucetLoc = this->setFaucet(boxSize);
        this->setSinks(boxSize);
        this->buildRoutes(); //Bonus +4 pts
        //allocating the rest of level's objects:
        for (int x = 0; x < LEVEL_SIZE; x++) {
            for (int y = 0; y < LEVEL_SIZE; y++) {
                if (m_map[x][y].get() == nullptr) {
                    randVal = (rand() % (20 - 10 + 1) / 2) * 2 + 10;
                    switch (randVal)
                    {
                    case STRAIGHT_PIPE_E:
                        m_map[x][y] = (std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * y + 64, boxSize.y * x + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E, STRAIGHT_PIPE_F, false));
                        break;
                    case T_PIPE_E:
                        m_map[x][y] = (std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * y + 64, boxSize.y * x + 64) + this->m_location, boxSize, T_PIPE_E, T_PIPE_F, false));
                        break;
                    case PLUS_PIPE_E:
                        m_map[x][y] = (std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * y + 64, boxSize.y * x + 64) + this->m_location, boxSize, PLUS_PIPE_E, PLUS_PIPE_F, false));
                        break;
                    case CORNER_PIPE_E:
                        m_map[x][y] = (std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * y + 64, boxSize.y * x + 64) + this->m_location, boxSize, CORNER_PIPE_E, CORNER_PIPE_F, false));
                        break;
                    default:
                        m_map[x][y] = (std::make_unique <Rotatable>(sf::Vector2f
                                (boxSize.x * y + 64, boxSize.y * x + 64) + this->m_location, boxSize, CORNER_PIPE_E, CORNER_PIPE_F, false));
                        break;
                    }
                }
            }
        }
    int rand;
    for (int i = 0; i < LEVEL_SIZE; ++i) {
        for (int j = 0; j < LEVEL_SIZE; ++j) {
            rand = std::rand() % 5;
            if (sf::Vector2f(i, j) == m_faucetLoc or sf::Vector2f(i, j) == m_sinkLoc)  continue;
            m_map[i][j].get()->setRunningWater(false);
            for (int k = 0; k < rand ; ++k) {
                m_map[i][j].get()->rotate();
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
                neighbours.push_back(m_map[row-1][col].get()); //up
            else
                neighbours.push_back(nullptr);
            if (row < m_map.size() - 1)
                neighbours.push_back(m_map[row+1][col].get()); //down
            else
                neighbours.push_back(nullptr);
            if (col > 0)
                neighbours.push_back(m_map[row][col-1].get()); //left
            else
                neighbours.push_back(nullptr);
            if (col < m_map.size() - 1)
                neighbours.push_back(m_map[row][col+1].get()); //right
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
void Board::setSinks(const sf::Vector2f& boxSize) {
    for (int sink = 0; sink < 1; sink++) {
        int randRow = std::rand() % LEVEL_SIZE;
        int randCol = std::rand() % LEVEL_SIZE;
        while (m_map[randRow][randCol].get() != nullptr) { //find empty place for new sink
            randRow = std::rand() % LEVEL_SIZE;
            randCol = std::rand() % LEVEL_SIZE;
        }
        this->m_map[randRow][randCol] = std::make_unique <Sink>(sf::Vector2f
        (boxSize.x * randCol + 64, boxSize.y * randRow + 64) + this->m_location, boxSize, SINK_E, SINK_F, false);
        //save the place of the sink in the DB:
        m_sinkLoc = (sf::Vector2f(randRow, randCol));
    }
}
//============================================================================
sf::Vector2f Board::setFaucet(const sf::Vector2f& boxSize) {
        int randRow = std::rand() % LEVEL_SIZE;
        int randCol = std::rand() % LEVEL_SIZE;
        while (m_map[randRow][randCol].get() != nullptr) {
            randRow = std::rand() % LEVEL_SIZE;
            randCol = std::rand() % LEVEL_SIZE;
        }
        this->m_map[randRow][randCol] = std::make_unique <Rotatable>(sf::Vector2f
        (boxSize.x * randCol + 64, boxSize.y * randRow + 64) + this->m_location, boxSize, FAUCET_F, FAUCET_F, true);

        return sf::Vector2f(randRow, randCol);
}
//============================================================================
void Board::InitializeMap() {
    for(int row =0 ; row< LEVEL_SIZE; row++)
        for (int col = 0; col < LEVEL_SIZE; col++)
            m_map[row].push_back(nullptr);
}
//============================================================================
std::vector<sf::Vector2f> Board::rafflePoints() {
    std::vector<sf::Vector2f> points = {};
    for (int point =0; point < ROUTE_POINTS; point++) {
        int randRow = std::rand() % LEVEL_SIZE;
        int randCol = std::rand() % LEVEL_SIZE;
        while (m_map[randRow][randCol].get() != nullptr or randRow < 0 or randCol < 0) { //find empty place for new sink
             randRow = std::rand() % LEVEL_SIZE;
             randCol = std::rand() % LEVEL_SIZE;
        }
        points.emplace_back(randRow, randCol);
    }
    return points;
}
//============================================================================
// this func builds the shortest possible route between 2 points
void Board::buildRoutePoint2Point(sf::Vector2f start,  sf::Vector2f end) {
    sf::Vector2f boxSize(BOX_WIDTH, BOX_HEIGHT);
    while (start != end) {
        if (start != m_faucetLoc or !isSink(start)) {
            if (start.x != end.x) { //diff rows
                if (end.y == start.y) { //same cols
                    if (end.x > start.x) { //end is below to start
                        start.x++;
                        if (m_map[int(start.x)][int(start.y)].get() != nullptr and start != end) {
                            if (start.y + 1 < BOARD_SIZE) start.y++;
                            else start.y--;
                            start.x--;
                            continue;
                        }
                        if (start == end) {
                            start.x--;
                            break;
                        }else{
                        this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E, STRAIGHT_PIPE_F, false);
                        }
                    }
                    else {//end is above to start
                        start.x--;
                        if (m_map[int(start.x)][int(start.y)].get() != nullptr and start != end) {
                            if (start.y + 1 < BOARD_SIZE) start.y++;
                            else start.y--;
                            start.x++;
                            continue;
                        }
                        if (start == end) {
                            start.x++;
                            break;
                        }else{
                        this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E, STRAIGHT_PIPE_F, false);
                        }
                    }
                }
                else { //diff rows
                    if (end.x > start.x) {
                        //case right
                        start.x++;
                        if (m_map[int(start.x)][int(start.y)].get() != nullptr and start != end) {
                            if (start.x + 1 < BOARD_SIZE) start.x++;
                            else start.x--;
                            start.x--;
                            continue;
                        }
                        if (start == end) {
                            start.x--;
                            break;
                        }else{
                        this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, T_PIPE_E, T_PIPE_F, false);
                        }
                    }
                    else {
                        //case left
                        start.x--;
                        if (start == end) {
                            start.x++;
                            break;
                        }else{
                        this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
                        (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, T_PIPE_E, T_PIPE_E, false);
                        }
                    }
                }
            }
            else { //same cols
                if (end.y < start.y) { // end above to start
                    start.y--;
                    if (start == end) {
                        start.y++;
                        break;
                    }else{
                    this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, STRAIGHT_PIPE_E, STRAIGHT_PIPE_F, false);
                     }
                }
                else {
                    start.y++;
                    if (m_map[int(start.x)][int(start.y)].get() != nullptr and start != end) {
                        if (start.y + 1 < BOARD_SIZE) start.y++;
                        else start.x--;
                        start.y--;
                        continue;
                    }
                    if (start == end) {
                        start.y--;
                        break;
                    }else{
                    this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
                    (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, CORNER_PIPE_E, CORNER_PIPE_F, false);
                    }
                }
            }
        }
        else {
            start.x++;

        }
    }

    if (m_map[int(start.x)][int(start.y)].get() == nullptr) {
        this->m_map[start.x][start.y] = std::make_unique <Rotatable>(sf::Vector2f
        (boxSize.x * start.y + 64, boxSize.y * start.x + 64) + this->m_location, boxSize, CORNER_PIPE_E, CORNER_PIPE_F, false);
    }
}
//============================================================================
void Board::buildRoutes() {
    std::vector<sf::Vector2f> routePoints = this->rafflePoints();
    buildRoutePoint2Point(m_sinkLoc,m_faucetLoc);
    //rotateSinkToPath();

}
//============================================================================
sf::Vector2f Board::findSinkDirection(Sink* sink, const sf::Vector2f& sinkLoc) {
    sf::Vector2f neighbourLoc = sinkLoc;
    switch (sink->getDirection()) {
    case UP:
        neighbourLoc.x--;
        break;
    case DOWN:
        neighbourLoc.x++;
        break;
    case LEFT:
        neighbourLoc.y--;
        break;
    case RIGHT:
        neighbourLoc.y++;
        break;
    }
    return neighbourLoc;
}
//============================================================================
bool Board::isSink(sf::Vector2f objLocation) {
    if (objLocation == m_sinkLoc){
            return true;
    }
    return false;
}
//============================================================================
void Board::rotateSinkToPath() {
    //down:
    if (dynamic_cast<Sink*>(m_map[m_sinkLoc.x][m_sinkLoc.y].get())) {


        if (m_map[m_sinkLoc.x + 1][m_sinkLoc.y].get() == nullptr) {
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->rotate();
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->rotate();
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->setDirections(false, true, false, false);
            dynamic_cast<Sink*>(m_map[m_sinkLoc.x][m_sinkLoc.y].get())->setDir(DOWN);
        } else if (m_map[m_sinkLoc.x][m_sinkLoc.y - 1].get() == nullptr) { //left
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->rotate();
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->rotate();
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->rotate();
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->setDirections(false, false, true, false);
            dynamic_cast<Sink*>(m_map[m_sinkLoc.x][m_sinkLoc.y].get())->setDir(LEFT);
        } else if (m_map[m_sinkLoc.x][m_sinkLoc.y + 1].get() == nullptr) { //right
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->rotate();
            m_map[m_sinkLoc.x][m_sinkLoc.y].get()->setDirections(false, false, false, true);
            dynamic_cast<Sink*>(m_map[m_sinkLoc.x][m_sinkLoc.y].get())->setDir(RIGHT);

        } // else is up- no changes needed.
    }
}
//============================================================================
void Board::runWater() {
    for (int i = 0; i < LEVEL_SIZE; ++i) {
        for (int j = 0; j < LEVEL_SIZE; ++j) {
            if (m_map[i][j].get()->getRunningWater()){
                //LOAD FULL TEXTURE
                m_map[i][j].get()->setTexture(1);
            }else {
                //LOAD EMPTY TEXTURE
                m_map[i][j].get()->setTexture(0);
            }
        }
    }
}
//============================================================================
void Board::runEvenMoreWater(int xCoord, int yCoord, int dir) {


    if (xCoord < 0) { //end of recursion
        //  xCoord++;
        return;
    }
    if (xCoord >= LEVEL_SIZE) {
        //  xCoord -= 1;
        return;
    }
    if (yCoord < 0) {
        // yCoord++;
        return;
    }
    if (yCoord >= LEVEL_SIZE) {
        //  yCoord--;
        return;
    }
    if (m_map[m_sinkLoc.x][m_sinkLoc.y].get()->getRunningWater())   m_solved = true;

    //applies to all if else conditions here:
    // this backtracking algorithm runs on every game tile (loops are avoided by checking for water
    // in the tiles and checking the direction the tile was called from)
    // every tile check for game board boarders and operates according to it.
    if (m_map[xCoord][yCoord].get()->getRunningWater()) {
        if (xCoord - 1 >= 0 and dir != UP) { ///ABOVE if in board range
            if (m_map[xCoord][yCoord].get()->getDirections().m_up and
                m_map[xCoord - 1][yCoord].get()->getDirections().m_down and
                    (not m_map[xCoord - 1][yCoord].get()->getRunningWater())) {

                m_map[xCoord - 1][yCoord].get()->setRunningWater(true);
                runEvenMoreWater(xCoord - 1, yCoord, DOWN);
            }
        }
        if (xCoord + 1 < LEVEL_SIZE and dir != DOWN) { ///BELOW if in board range
            if (m_map[xCoord][yCoord].get()->getDirections().m_down and
                m_map[xCoord + 1][yCoord].get()->getDirections().m_up and
                        (not m_map[xCoord + 1][yCoord].get()->getRunningWater())) {

                m_map[xCoord + 1][yCoord].get()->setRunningWater(true);
                runEvenMoreWater(xCoord + 1, yCoord, UP);
            }
        }
        if (yCoord - 1 >= 0 and dir != LEFT) { ///LEFT if in board range
            if (m_map[xCoord][yCoord].get()->getDirections().m_left and
                m_map[xCoord][yCoord - 1].get()->getDirections().m_right and
                (not m_map[xCoord][yCoord - 1].get()->getRunningWater())) {

                m_map[xCoord][yCoord - 1].get()->setRunningWater(true);
                runEvenMoreWater(xCoord, yCoord - 1, RIGHT);
            }
        }
        if (yCoord + 1 < LEVEL_SIZE and dir != RIGHT) { ///RIGHT if in board range
            if (m_map[xCoord][yCoord].get()->getDirections().m_right and
                m_map[xCoord][yCoord + 1].get()->getDirections().m_left and
                (not m_map[xCoord][yCoord + 1].get()->getRunningWater())) {

                m_map[xCoord][yCoord + 1].get()->setRunningWater(true);
                runEvenMoreWater(xCoord, yCoord + 1, LEFT);
            }
        }
    }
}

//============================================================================
bool Board::getWaterInSink() const {
    return m_solved;
}