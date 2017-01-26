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

class Maze {
public:
	Maze(int w, int h);
	Maze(std::string filename);

	void reset(int w, int h);
	void importFromFile(std::string filename);
	void exportToFile(std::string filename);
	void generate(int xStart, int yStart);
	void draw(SDL2pp::Renderer &renderer, int scale);

	friend std::ostream& operator<< (std::ostream &out, Maze &m);
	friend class AStar;

private:
	std::vector<std::vector<Cell>> grid;
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
