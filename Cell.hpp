//
// Created by roscale on 1/20/17.
//

#ifndef MAZE_GENERATOR_CELL_HPP
#define MAZE_GENERATOR_CELL_HPP


#include <array>
#include <SDL2pp/Renderer.hh>

class Cell {
public:
	Cell(int x, int y);

	enum Wall
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	bool hasBeenVisited() const;
	void markAsVisited();
	void removeWall(Wall wallToRemove);
	void draw(SDL2pp::Renderer &renderer, int size) const;

	friend std::ostream& operator<< (std::ostream &out, Cell &c);
	friend class MazeGenerator;

private:
	int x;
	int y;

	bool visited = false;
	std::array<bool, 4> walls = { true, true, true, true };
};


#endif //MAZE_GENERATOR_CELL_HPP
