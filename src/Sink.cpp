#include "Sink.h"
#include "Resources.h"
#include "Macros.h"

Sink::Sink(const sf::Vector2f& location,
	const sf::Vector2f& size, int empty, int full, bool water)
	: Square(location, size, empty, full, water) {
    m_shapes.push_back(Resources::instance().getTexture(empty));
    m_shapes.push_back(Resources::instance().getTexture(full));
	this->getShape().setTexture(m_shapes[0]); //0 for empty
	this->getShape().setOrigin(this->getShape().getGlobalBounds().width / 2,
		this->getShape().getGlobalBounds().height / 2);
	this->getShape().setPosition(location);
	std::srand(time(nullptr));
	int randDirection;
	bool validLoc = false;
//	while (!validLoc) {
//        randDirection = std::rand() % DIRECTIONS_NUM;
//        switch (randDirection) {
//// this code section verifies that the location of the sink will always be valid. meaning- the sink's opening
//// will never face the outside of the board
//            case DOWN:
//                // below board constraints
//                if (location.y + 128  > BOARD_SIZE + int((HEIGHT - BOARD_SIZE) / 2))     continue;
//                this->rotate();
//                this->rotate();
//                setDirections(false, true, false, false);
//                m_direction = DOWN;
//                validLoc = true;
//                break;
//            case LEFT:
//                if (location.x - 128  < int((WIDTH - BOARD_SIZE) / 2))     continue;
//                this->rotate();
//                this->rotate();
//                this->rotate();
//                setDirections(false, false, true, false);
//                m_direction = LEFT;
//                validLoc = true;
//                break;
//            case RIGHT:
//                if (location.x + 128  > BOARD_SIZE + int((WIDTH - BOARD_SIZE) / 2))     continue;
//                this->rotate();
//                setDirections(false, false, false, true);
//                m_direction = RIGHT;
//                validLoc = true;
//                break;
//            default:
//                // above board boarders
//                if (location.y - 128  < int((HEIGHT - BOARD_SIZE) / 2))     continue;
//                setDirections(true, false, false, false);
//                m_direction = UP;
//                validLoc = true;
//                break;
//        }
//    }
}

int Sink::getDirection()const {
	return m_direction;
}


void Sink::setDir(int dir) {
    m_direction = dir;
}