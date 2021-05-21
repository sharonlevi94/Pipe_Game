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
        : m_levelReader(DataReader()),
          m_location(location),
           m_size(size){}
//================================ gets section ==============================
//============================================================================
const sf::Vector2f& Board::getLevelSize()const { return this->m_size; }
//============================================================================
const sf::Vector2f& Board::getLocation() const { return this->m_location; }
//============================================================================
const Square* Board::getContent(const sf::Vector2f& location) const {
//    if (!this->m_background.getGlobalBounds().contains(location))
//        return nullptr;
    if(location.x>=m_location.x && location.x<= m_location.x+m_size.x)
        if (location.y >= m_location.y && location.y <= m_location.y + m_size.y) {
            int x = (int)((location.x - this->m_location.x) / (this->getLevelSize().x / this->m_map[0].size()));
            int y = (int)((location.y - this->m_location.y) / (this->getLevelSize().y / this->m_map.size()));

            if ((Rotatable*)(this->m_map[y][x].get()))
                return ((Rotatable*)this->m_map[y][x].get());
        }
    return nullptr;
}
//============================================================================
Square* Board::getContent(const sf::Vector2f& location) {
    if (location.x >= m_location.x && location.x <= m_location.x + m_size.x)
        if (location.y >= m_location.y && location.y <= m_location.y + m_size.y) {
            int x = (int)((location.x - this->m_location.x) /
                (this->getLevelSize().x / this->m_map[0].size())),
                y = (int)((location.y - this->m_location.y) /
                    (this->getLevelSize().y / this->m_map.size()));

            if ((Rotatable*)(this->m_map[y][x].get()))
                return ((Rotatable*)this->m_map[y][x].get());
        }
    return nullptr;
}
//============================================================================
sf::Vector2f Board::getObjectSize()const{
    return sf::Vector2f{this->getLevelSize().x / this->m_map[0].size(),
                         this->getLevelSize().y / this->m_map.size() };
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
    
    vector<vector<char>> map = m_levelReader.readNextLevel();
    vector<Rotatable*> faucetVec = {};
    
   // sf::Vector2f boxSize(this->getLevelSize().x / map[0].size(),
   //                      this->getLevelSize().y / map.size());

    sf::Vector2f boxSize(128,128);

    //reset last load parameters:
    this->releaseMap();
    this->m_map.resize(map.size());

    //allocating level's objects:
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); x++) {
            switch (map[y][x])
            {
            case STRAIGHT_PIPE:
                this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                (boxSize.x * x + 32, boxSize.y * y - 16) + this->m_location, boxSize, STRAIGHT_PIPE_E));
                break;
            case T_PIPE:
                this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y) + this->m_location, boxSize, T_PIPE_E));
                break;
            case PLUS_PIPE:
                this->m_map[y].push_back(std::make_unique <Square>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y - 32) + this->m_location, boxSize, PLUS_PIPE_E));
                break;
            case CORNER_PIPE:
                this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                (boxSize.x * x + 32, boxSize.y * y) + this->m_location, boxSize, CORNER_PIPE_E));
                break;
            case SINK_UP:
                this->m_map[y].push_back(std::make_unique <Sink>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y) + this->m_location, boxSize, SINK_E, SINK_UP));
                break;
            case SINK_DOWN:
                this->m_map[y].push_back(std::make_unique <Sink>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y) + this->m_location, boxSize, SINK_E, SINK_DOWN));
                break;
            case SINK_LEFT:
                this->m_map[y].push_back(std::make_unique <Sink>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y) + this->m_location, boxSize, SINK_E, SINK_LEFT));
                break;
            case SINK_RIGHT:
                this->m_map[y].push_back(std::make_unique <Sink>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y) + this->m_location, boxSize, SINK_E, SINK_RIGHT));
                break;
            case FAUCET:
                this->m_map[y].push_back(std::make_unique <Rotatable>(sf::Vector2f
                (boxSize.x * x, boxSize.y * y) + this->m_location, boxSize, FAUCET_F));
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
//the method isn't const because fstream's peek method isn't const
bool Board::is_next_lvl_exist() const{
    return m_levelReader.isThereNextLevel();
}
//============================================================================
/*
* This function load the background and the music of the current level.
*/
void Board::loadLevelEffects() {
    //Resources::instance().playMusic();
}
//============================== private section =============================
void Board::releaseMap() {
    this->m_map.clear();
}
