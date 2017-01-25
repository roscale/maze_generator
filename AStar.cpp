//
// Created by roscale on 1/25/17.
//

#include <cmath>
#include "AStar.hpp"

float AStar::heuristic(const Node &n1, const Node &n2) {
	float distX = n1.x - n2.x;
	float distY = n1.y - n2.y;
	return static_cast<float>(sqrt(distX*distX + distY*distY));
}
