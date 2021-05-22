#pragma once
#include <algorithm>
#include "Square.h"
#include <vector>
#include "Sink.h"
#include <memory>

class Graph {
public:
	Graph(std::vector<std::vector<std::unique_ptr<Square>>>);
	bool bfs(Square* source, Square* end);
private:
	std::vector<std::vector<std::unique_ptr<Square>>> m_nodes;
	std::vector<std::unique_ptr<Square>> m_neighbours;
	std::vector<std::unique_ptr<Sink>> m_sinks;
};