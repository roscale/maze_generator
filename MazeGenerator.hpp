//
// Created by roscale on 1/20/17.
//

#ifndef MAZE_GENERATOR_GENERATOR_HPP
#define MAZE_GENERATOR_GENERATOR_HPP


#include <vector>
#include <stack>
#include <functional>
#include <SDL2pp/Renderer.hh>
#include "Cell.hpp"

class MazeGenerator {
public:
	MazeGenerator(int w, int h, int xStart, int yStart);

	void generate();
	void draw(SDL2pp::Renderer &renderer, int size);

	friend std::ostream& operator<< (std::ostream &out, MazeGenerator &m);

private:
	std::vector<std::vector<Cell>> maze;
	int width;
	int height;

	Cell *current;
	std::stack<std::reference_wrapper<Cell>> stack;

	bool unvisitedCells() const;
	bool hasUnvisitedNeighbours(const Cell &c) const;
	Cell& getRandomUnvisitedNeighbour(const Cell &c);
	static void removeWalls(Cell &c1, Cell &c2);
};


#endif //MAZE_GENERATOR_GENERATOR_HPP
