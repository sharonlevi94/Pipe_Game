//============================= include section ==============================
#include "DataReader.h"
#include "Macros.h"
#include <iostream>

using std::endl;
using std::vector;
//============================= public section ===============================
//==================== Constructors & distructors section ====================
DataReader::DataReader()
        : m_levelSize({}){
    m_boardReader.open("Board.txt");
    if(!this->m_boardReader.is_open())
        throw std::ifstream::failure
        ("Cannot open the levels file, pls make sure the file is exist");

}
//========================================================================
DataReader::~DataReader() {
    this->m_boardReader.close();
}
/*============================ methods section ===============================
//========================================================================
  This function return true if a new level is exist in the inputed file
  or false if all the levels is over.
*/
bool DataReader::isThereNextLevel()const {
    return (!this->m_boardReader.eof());
}
//========================================================================
/*
* this function read the parameters from the level and then level itself
* from the file.
*/
vector<vector<char>> DataReader::readNextLevel(){
    //1. allocate 2D vector of chars
    vector<vector<char>> newLevel = {};
    //2. check first if there is more level in the file
    if (this->isThereNextLevel()) {
        char input;
    //3. receive level size
        m_boardReader >> m_levelSize.x >> m_levelSize.y;
        m_boardReader.get();
    //4. read the level itself from the file
        for (int i = 0; i < m_levelSize.x; i++) {
            std::vector<char> row = {};
            for (int j = 0; j < m_levelSize.y; j++) {
                m_boardReader.get(input);
                switch (input)
                {
                case STRAIGHT_PIPE: {
                    row.push_back(STRAIGHT_PIPE);
                    break;
                }
                case CORNER_PIPE: {
                    row.push_back(CORNER_PIPE);
                    break;
                }
                case PLUS_PIPE: {
                    row.push_back(PLUS_PIPE);
                    break;
                }
                case T_PIPE: {
                    row.push_back(T_PIPE);
                    break;
                }
                case SINK: {
                    row.push_back(SINK);
                    break;
                }
                case FAUCET: {
                    row.push_back(FAUCET);
                    break;
                }
                default: {
                    row.push_back('\0'); // inputed ' '
                    break;
                }
                }
            }
            if (m_boardReader.peek() != '\0')
                m_boardReader.get(input);
            newLevel.push_back(row);
        }
        m_boardReader.get(input);
    }
    return newLevel;
}
//========================================================================
sf::Vector2f DataReader::getLevelSize()const { return this->m_levelSize; }
//========================================================================
/*this function return the file descriptor to the beginning of the file
* and clear the current vector of the map.
 */
void DataReader::resetRead() {
    this->m_boardReader.clear();
    this->m_boardReader.seekg(0);
    this->m_levelSize = {0, 0};
}