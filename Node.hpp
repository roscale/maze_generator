//
// Created by roscale on 1/25/17.
//

#ifndef MAZE_GENERATOR_NODE_HPP
#define MAZE_GENERATOR_NODE_HPP


#include <vector>

class Node {
private:
	int x;
	int y;

	std::vector<std::reference_wrapper<Node>> openSet;
	decltype(openSet) closedSet;

	float gScore;

	friend class AStar;
};


#endif //MAZE_GENERATOR_NODE_HPP
