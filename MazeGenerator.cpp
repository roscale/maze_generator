//
// Created by roscale on 1/20/17.
//

#include <cstdlib>
#include "MazeGenerator.hpp"

MazeGenerator::MazeGenerator(int w, int h, int xStart, int yStart) : width{w}, height{h}
{
	assert(xStart >= 0 && xStart < width);
	assert(yStart >= 0 && yStart < height);

	// Create cells each one having its position as member
	for (int i = 0; i < width; ++i) {
		std::vector<Cell> column;
		for (int j = 0; j < height; ++j)
			column.emplace_back(i, j);

		maze.push_back(column);
	}

	// Set the starting cell
	current = &(maze[xStart][yStart]);
}

void MazeGenerator::generate() {
	current->markAsVisited();

	while (unvisitedCells()) {
		if (hasUnvisitedNeighbours(*current)) {
			Cell &randomNeighbour = getRandomUnvisitedNeighbour(*current);
			stack.push(randomNeighbour);
			removeWalls(*current, randomNeighbour);
			current = &randomNeighbour;
			current->markAsVisited();
		}
		else if (!stack.empty()) {
			current = &(stack.top().get());
			stack.pop();
		}
	}
}

void MazeGenerator::draw(SDL2pp::Renderer &renderer, int size) {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			maze[i][j].draw(renderer, size);
		}
	}
}

std::ostream &operator<<(std::ostream &out, MazeGenerator &m) {
	for (int i = 0; i < m.width; ++i) {
		for (int j = 0; j < m.height; ++j) {
			out << m.maze[i][j] << ' ';
		}
		out << '\n';
	}
	return out;
}

bool MazeGenerator::unvisitedCells() const {
	for (const auto &column : this->maze)
		for (const auto &cell : column)
			if (!cell.hasBeenVisited())
				return true;
	return false;
}

bool MazeGenerator::hasUnvisitedNeighbours(const Cell &c) const {
	for (int offset : {-1, 1}) {

		const int &leftRight = c.x + offset;
		// Check edge cases of the neighbour
		if (leftRight >= 0 && c.y >= 0 && leftRight < width && c.y < height)
			if (!maze[leftRight][c.y].hasBeenVisited())
				return true;

		const int &upDown = c.y + offset;
		if (c.x >= 0 && upDown >= 0 && c.x < width && upDown < height)
			if (!maze[c.x][upDown].hasBeenVisited())
				return true;
	}
	return false;
}

Cell& MazeGenerator::getRandomUnvisitedNeighbour(const Cell &c) {
	std::vector<std::reference_wrapper<Cell>> unvisitedNeighbours;

	for (int offset : {-1, 1}) {

		const int &leftRight = c.x + offset;
		if (leftRight >= 0 && c.y >= 0 && leftRight < width && c.y < height) {
			Cell &neighbour = maze[leftRight][c.y];

			if (!neighbour.hasBeenVisited())
				unvisitedNeighbours.push_back(neighbour);
		}

		const int &upDown = c.y + offset;
		if (c.x >= 0 && upDown >= 0 && c.x < width && upDown < height) {
			Cell &neighbour = maze[c.x][upDown];

			if (!neighbour.hasBeenVisited())
				unvisitedNeighbours.push_back(neighbour);
		}
	}
	return unvisitedNeighbours[rand() % unvisitedNeighbours.size()];
}

void MazeGenerator::removeWalls(Cell &c1, Cell &c2) {
	int diff = c1.x - c2.x;
	if (diff != 0) {
		c1.removeWall((diff == -1) ? Cell::RIGHT : Cell::LEFT);
		c2.removeWall((diff == -1) ? Cell::LEFT : Cell::RIGHT);
	}

	diff = c1.y - c2.y;
	if (diff != 0) {
		c1.removeWall((diff == -1) ? Cell::DOWN : Cell::UP);
		c2.removeWall((diff == -1) ? Cell::UP : Cell::DOWN);
	}
}
