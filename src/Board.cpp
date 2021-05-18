//============================= include section ==========================
#include "Board.h"


using std::vector;
//====================== Constructors & distructors section ==================
Board::Board(const sf::Vector2f& location,
             const sf::Vector2f& size)
        : m_levelReader(DataReader()),
          m_background(sf::RectangleShape()),
          m_location(location){
    this->m_background.setSize(size);
    m_background.setPosition(m_location);
}
//================================ gets section ==============================
//============================================================================
const sf::Vector2f& Board::getlevelSize()const {
    return this->m_background.getSize();
}
//============================================================================
const sf::Vector2f& Board::getLocation() const {
    return this->m_location;
}

//============================================================================
const StaticObject* Board::getContent(const sf::Vector2f& location) const {
    if (!this->m_background.getGlobalBounds().contains(location))
        return nullptr;
    int x = (int)((location.x - this->m_location.x) /
                  (this->getlevelSize().x / this->m_map[0].size())),
            y = (int)((location.y - this->m_location.y) /
                      (this->getlevelSize().y / this->m_map.size()));
//    if (dynamic_cast <StaticObject*> (this->m_map[y][x].get()))
//        return ((StaticObject*)this->m_map[y][x].get());
    return nullptr;
}
//============================================================================
sf::Vector2f Board::getObjectSize()const{
    return sf::Vector2f{ this->getlevelSize().x / this->m_map[0].size(),
                         this->getlevelSize().y / this->m_map.size() };
}
//============================ methods section ===============================
void Board::draw(sf::RenderWindow& window,
                 const sf::Time& deltaTime){
    window.draw(m_background);
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
vector<MovingObject*> Board::loadNewLevel() {
    vector<vector<char>> map = m_levelReader.readNextLevel();
    vector<MovingObject*> movingsVec = {};
    sf::Vector2f boxSize(this->getlevelSize().x / map[0].size(),
                         this->getlevelSize().y / map.size());

    //reset last load parameters:
    this->releaseMap();
    this->clearParameters();
    this->m_map.resize(map.size());

    //allocating level's objects:
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); x++) {
            switch (map[y][x])
            {

                default:
                    this->m_map[y].push_back(nullptr); // inputed ' '
                    break;
            }
        }
    }
    return movingsVec;
}
//============================================================================
//the method isn't const because fstream's peek method isn't const
bool Board::is_next_lvl_exist() const{
    return m_levelReader.isThereNextLevel();
}
//============================================================================
bool Board::isMovePossible(const sf::Vector2f& location) const {
    if (this->m_background.getGlobalBounds().contains(location))
        return true;
    return false;
}
//============================================================================
/*
* This function pass all the map and reset every object to the initial location
* and state.
*/
void Board::resetLvl(){
    for (int i = 0; i < this->m_map.size(); ++i)
        for (int j = 0; j < this->m_map[i].size(); ++j) {
            if(this->m_map[i][j].get() != nullptr)
                this->m_map[i][j]->reset();
        }
}
//============================================================================
void Board::gameOver() {
    this->m_levelReader.resetRead();
    this->releaseMap();
}
//============================================================================
/*
* This function load the background and the music of the current level.
*/
void Board::loadLevelEffects(int level) {
    this->m_background.setTexture(&Resources::instance()
            .getBackground(level));
    Resources::instance().playMusic(level);
}
//============================== private section =============================
void Board::releaseMap() {
    this->m_map.clear();
}
//============================================================================
/*this function all the details of the current level, release ptrs and 
unique ptrs.*/
void Board::clearParameters() {
    this->releaseMap();
}