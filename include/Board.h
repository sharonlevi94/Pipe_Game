#pragma once
//============================ include section ===============================
#include <vector>
#include "DataReader.h"
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "Resources.h"
#include <vector>
//========================== forward declarations ============================
class MovingObject;
class GameObject;
class StaticObject;
class Enemy;
class Gift;
class Player;
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
    int getLevelTime()const;
    const sf::Vector2f& getlevelSize()const;
    const sf::Vector2f& getLocation() const;
    sf::Vector2f getObjectSize()const;
    StaticObject* getContent(const sf::Vector2f& location);
    const StaticObject* getContent(const sf::Vector2f&) const;
    const sf::Vector2f& getPlayerLoc()const;
    const sf::Vector2f& getDoorLocation()const;

    //=========================== method section =============================
    void draw(sf::RenderWindow& window, const sf::Time&);
    vector<MovingObject*>loadNewLevel();
    bool is_next_lvl_exist()const;
    void resetLvl();
    void gameOver();
    bool isMovePossible(const sf::Vector2f&)const;
    void loadLevelEffects(int);

private:
    //========================= members section ==============================
    vector<vector<std::unique_ptr<GameObject>>> m_map;
    sf::Vector2f m_location;
    DataReader m_levelReader;
    sf::RectangleShape m_background;
    //====================== privete methods section =========================
    void releaseMap();
    void clearParameters();
};