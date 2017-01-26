//
// Created by roscale on 1/20/17.
//

#ifndef MAZE_GENERATOR_CELL_HPP
#define MAZE_GENERATOR_CELL_HPP


#include <array>
#include <SDL2pp/Renderer.hh>
#include "Node.hpp"

class Cell : public Node {
public:
	Cell(int x, int y);

	enum Wall
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MAX_WALLS
	};

	bool hasBeenVisited() const;
	void markAsVisited();
	void removeWall(Wall wallToRemove);
	void setWalls(std::string strWalls);
	void draw(SDL2pp::Renderer &renderer, int size) const;

	friend bool operator==(const Cell &c1, const Cell &c2);
	friend std::ostream& operator<< (std::ostream &out, Cell &c);
	friend class Maze;
	friend class AStar;

private:
	int x;
	int y;

	bool visited = false;
	std::array<bool, 4> walls = { true, true, true, true };
};


#endif //MAZE_GENERATOR_CELL_HPP
