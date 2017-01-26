//
// Created by roscale on 1/25/17.
//

#ifndef MAZE_GENERATOR_NODE_HPP
#define MAZE_GENERATOR_NODE_HPP


#include <vector>
class Cell;

class Node {
protected:
	float gScore = 0.0f;
	float fScore = 0.0f;
	Cell *cameFrom = nullptr;

	friend class AStar;
};


#endif //MAZE_GENERATOR_NODE_HPP
