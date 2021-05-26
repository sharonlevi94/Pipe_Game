#pragma once
//============================ include section ===============================
#include <vector>
#include "Square.h"
#include "Sink.h"
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
    void loadNewLevel();
    void calcNeighbours();
    void loadLevelEffects();
    bool getWaterInSink() const;


private:
    //========================= members section ==============================
    vector<vector<std::unique_ptr<Square>>> m_map;
    sf::Vector2f m_location;
    sf::Vector2f m_size;
    sf::Vector2f m_faucetLoc;
    sf::Vector2f m_sinkLoc;
    //====================== privete methods section =========================
    void releaseMap();
    void buildRoutes();
    void setSinks(const sf::Vector2f&);
    sf::Vector2f setFaucet(const sf::Vector2f&);
    void InitializeMap();
    std::vector<sf::Vector2f> rafflePoints();
    void buildRoutePoint2Point( sf::Vector2f,  sf::Vector2f);
    bool isSink(sf::Vector2f);
    void rotateSinkToPath();
    void runWater();
    bool m_solved;
    void runEvenMoreWater(int, int, int);
};