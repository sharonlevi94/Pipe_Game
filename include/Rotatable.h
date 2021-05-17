#pragma once
#include "Square.h"

class Rotatable : public Square {
public:
	using Square::Square;
	void rotate();
};