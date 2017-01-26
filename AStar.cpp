//
// Created by roscale on 1/25/17.
//

#include <algorithm>
#include <cmath>
#include "AStar.hpp"

AStar::AStar(Maze &m) : maze{&m} {
}

void AStar::resolve(int xStart, int yStart, int xGoal, int yGoal) {
	assert(xStart >= 0 && xStart < maze->width);
	assert(yStart >= 0 && yStart < maze->height);
	assert(xGoal >= 0 && xGoal < maze->width);
	assert(yStart >= 0 && yStart < maze->height);

	Cell &start = maze->grid[xStart][yStart];
	Cell &goal = maze->grid[xGoal][yGoal];
	Cell *current = nullptr;

	openSet.push_back(&start);

	while (!openSet.empty()) {
		current = lowestScore(openSet);

		if (*current == goal) {
			break;
		}

		openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
		closedSet.push_back(current);

		for (auto *neighbour : getNeighboursOf(*current)){
			// If it's in the closedSet
			if (std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end())
				continue;

			float tentative_gScore = current->gScore + 1;
			// If it's in the openSet
			if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
				openSet.push_back(neighbour);

			else if (tentative_gScore >= neighbour->gScore)
				continue;

			neighbour->cameFrom = current;
			neighbour->gScore = tentative_gScore;
			neighbour->fScore =neighbour->gScore + heuristic(*neighbour, goal);
		}
	}
	// Reconstruct the path even if the goal isn't reached
	reconstructPath(current);
}

Cell *AStar::lowestScore(std::vector<Cell *> vector) {
	if (vector.empty())
		return nullptr;

	Cell *lowest = vector[0];

	for (auto *Cell : vector)
		if (Cell->fScore < lowest->fScore)
			lowest = Cell;

	return lowest;
}

std::vector<Cell *> AStar::getNeighboursOf(const Cell &n) {
	std::vector<Cell *> neighbours;

	const int &up = n.y + -1;
	if (up >= 0 && up < maze->height)
		if (!n.walls[n.UP])
			neighbours.push_back(&maze->grid[n.x][up]);

	const int &down = n.y + 1;
	if (down >= 0 && down < maze->height)
		if (!n.walls[n.DOWN])
			neighbours.push_back(&maze->grid[n.x][down]);

	const int &left = n.x + -1;
	if (left >= 0 && left < maze->width)
		if (!n.walls[n.LEFT])
			neighbours.push_back(&maze->grid[left][n.y]);

	const int &right = n.x + 1;
	if (right >= 0 && right < maze->width)
		if (!n.walls[n.RIGHT])
			neighbours.push_back(&maze->grid[right][n.y]);

	return neighbours;
}

float AStar::heuristic(const Cell &n1, const Cell &n2) {
	float distX = n1.x - n2.x;
	float distY = n1.y - n2.y;
	return static_cast<float>(sqrt(distX*distX + distY*distY));
}

void AStar::reconstructPath(Cell *n) {
	std::vector<Cell *> path;

	while (n) {
		path.push_back(n);
		n = n->cameFrom;
	}

	this->path = path;
}

void AStar::draw(SDL2pp::Renderer &renderer, int scale) {
	renderer.SetDrawColor(255, 0, 0);

	for (int i = 0; i < path.size()-1; ++i) {
		const int &x1 = path[i]->x*scale;
		const int &y1 = path[i]->y*scale;
		const int &x2 = path[i+1]->x*scale;
		const int &y2 = path[i+1]->y*scale;

		renderer.DrawLine(x1+scale/2, y1+scale/2, x2+scale/2, y2+scale/2);
	}
}
