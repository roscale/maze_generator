//
// Created by roscale on 1/20/17.
//

#include "Cell.hpp"

Cell::Cell(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Cell::hasBeenVisited() const {
	return visited;
}

void Cell::markAsVisited() {
	visited = true;
}

void Cell::removeWall(Cell::Wall wallToRemove) {
	walls[wallToRemove] = false;
}

void Cell::setWalls(std::string strWalls) {
	for (int w = 0; w < MAX_WALLS; ++w) {
		walls[w] = strWalls[w] - '0';
		// std::clog << walls[w];
	}
}

void Cell::draw(SDL2pp::Renderer &renderer, int size) const{
	renderer.SetDrawColor(0, 0, 0);
	if (walls[UP])
		renderer.DrawLine(x*size, y*size, x*size+size, y*size);
	if (walls[DOWN])
		renderer.DrawLine(x*size, y*size+size, x*size+size, y*size+size);
	if (walls[LEFT])
		renderer.DrawLine(x*size, y*size, x*size, y*size+size);
	if (walls[RIGHT])
		renderer.DrawLine(x*size+size, y*size, x*size+size, y*size+size);
}

std::ostream& operator<<(std::ostream &out, Cell &c) {
	std::string strWalls;
	for (int w = 0; w < c.MAX_WALLS; ++w) {
		strWalls += (c.walls[w] + '0');
	}
	out << strWalls;
	return out;
}

