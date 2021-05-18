#pragma once
#include "Square.h"
#include "Directions.h"
class Rotatable : public Square {
public:
	using Square::Square;
	void rotate();
private:
	struct Directions m_Directions;
};