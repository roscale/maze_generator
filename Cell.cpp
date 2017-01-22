//
// Created by roscale on 1/20/17.
//

#include "Cell.hpp"

Cell::Cell(int x, int y) {
	this->x = x;
	this->y = y;
}

void Cell::markAsVisited() {
	visited = true;
}

void Cell::removeWall(Cell::Wall wallToRemove) {
	walls[wallToRemove] = false;
}

bool Cell::hasBeenVisited() const {
	return visited;
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
	out << "(" << c.x << ", " << c.y << ")";
	return out;
}
