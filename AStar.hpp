//
// Created by roscale on 1/25/17.
//

#ifndef MAZE_GENERATOR_ASTAR_HPP
#define MAZE_GENERATOR_ASTAR_HPP


#include <SDL2pp/Renderer.hh>
#include "Cell.hpp"
#include "Maze.hpp"

class AStar {
public:
	AStar(Maze &m);

	void resolve(int xStart, int yStart, int xGoal, int yGoal);
	void draw(SDL2pp::Renderer &renderer, int scale);

private:
	Maze *maze;

	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	std::vector<Cell*> path;

	float gScore = 0.0f;
	float fScore = 0.0f;

	static Cell *lowestScore(std::vector<Cell *> vector);
	std::vector<Cell *> getNeighboursOf(const Cell &n);
	static float heuristic(const Cell &n1, const Cell &n2);
	void reconstructPath(Cell *n);
};


#endif //MAZE_GENERATOR_ASTAR_HPP
