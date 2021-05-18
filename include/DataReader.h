#pragma once
//============================= include section ==============================
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

class DataReader{
public:
    //========================= constructors section =========================
    DataReader();
    ~DataReader();
    //============================= gets section =============================

    sf::Vector2f getLevelSize()const;
    int getLevelTime()const;
    //========================== method section ==============================

    bool isThereNextLevel()const;
    std::vector<std::vector<char>> readNextLevel();
    void resetRead();
private:
    //====================== privete methods section =========================

    void receiveLevelParameters();
    //======================== members section ===============================

    std::ifstream m_boardReader;
    sf::Vector2f m_levelSize;
};