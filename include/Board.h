#pragma once
//============================ include section ===============================
#include <vector>
//#include <DataReader.h>
#include "Square.h"
//========================== forward declarations ============================
//class Square;
class Rotatable;
//============================== using section ===============================
using std::vector;
/*============================================================================
 * Class: Board.
 * the board contain and draw the level's objects.
 * alse the board helps the
 * read the levels from the file by one of its member.
 * also the board help
 */
class Board
{
public:
    //================= constractors and destractors section =================
    Board(const sf::Vector2f& location = sf::Vector2f(0,0),
          const sf::Vector2f& size = sf::Vector2f(0,0));
    ~Board() = default;
    //============================ gets section ==============================
    Square* getContent(const sf::Vector2f&);
    //=========================== method section =============================
    void draw(sf::RenderWindow& );
    vector<Rotatable*>loadNewLevel();
    void calcNeighbours();
    void loadLevelEffects();

private:
    //========================= members section ==============================
    vector<vector<std::unique_ptr<Square>>> m_map;
    sf::Vector2f m_location;
    sf::Vector2f m_size;
    vector<Rotatable*> m_faucets;

    //====================== privete methods section =========================
    void releaseMap();
    void calcInernalNeighbours();
    void calcFirstColNeighbours();
    void calcLastColNeighbours();
};