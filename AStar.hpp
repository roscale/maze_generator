//
// Created by roscale on 1/25/17.
//

#ifndef MAZE_GENERATOR_ASTAR_HPP
#define MAZE_GENERATOR_ASTAR_HPP


#include "Node.hpp"

class AStar {
private:
	float gScore = 0.0f;
	float fScore = 0.0f;

	float heuristic(const Node &n1, const Node &n2);
};


#endif //MAZE_GENERATOR_ASTAR_HPP
