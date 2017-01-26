//
// Created by roscale on 1/20/17.
//

#include <cstdlib>
#include <fstream>
#include "Maze.hpp"

Maze::Maze(int w, int h) {
	reset(w, h);
}

Maze::Maze(std::string filename) {
	importFromFile(filename);
}

void Maze::reset(int w, int h) {
	width = w;
	height = h;

	// Create cells each one having its position as member
	grid.clear();
	for (int i = 0; i < width; ++i) {
		std::vector<Cell> column;
		for (int j = 0; j < height; ++j)
			column.emplace_back(i, j);

		grid.push_back(column);
	}
}

void Maze::importFromFile(std::string filename) {
	std::ifstream in(filename);
	assert(in && "File could not be opened");

	in >> width;
	in >> height;
	// std::clog << width;

	// Create cells and modify the walls
	grid.clear();
	for (int i = 0; i < width; ++i) {
		std::vector<Cell> column;
		for (int j = 0; j < height; ++j) {
			column.emplace_back(i, j);

			// Set the walls
			std::string strWalls;
			in >> strWalls;
			column.back().setWalls(strWalls);
		}
		grid.push_back(column);
	}


	// std::clog << *this;
}

void Maze::exportToFile(std::string filename)
{
	std::ofstream out(filename);
	assert(out && "File could not be opened");

	// Write the dimension of the matrix
	out << width << " " << height << '\n';

	// Write each cell's wall
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			for (const bool &wall : grid[i][j].walls)
				out << wall;
			out << ' ';
		}
		out << '\n';
	}
}

void Maze::generate(int xStart, int yStart) {
	assert(xStart >= 0 && xStart < width);
	assert(yStart >= 0 && yStart < height);

	// Set the starting cell
	current = &(grid[xStart][yStart]);

	// The algorithm like on wikipedia
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

void Maze::draw(SDL2pp::Renderer &renderer, int scale) {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			grid[i][j].draw(renderer, scale);
		}
	}
}

std::ostream &operator<<(std::ostream &out, Maze &m) {
	for (int i = 0; i < m.width; ++i) {
		for (int j = 0; j < m.height; ++j) {
			out << m.grid[i][j] << ' ';
		}
		out << '\n';
	}
	return out;
}

bool Maze::unvisitedCells() const {
	for (const auto &column : this->grid)
		for (const auto &cell : column)
			if (!cell.hasBeenVisited())
				return true;
	return false;
}

bool Maze::hasUnvisitedNeighbours(const Cell &c) const {
	for (int offset : {-1, 1}) {

		const int &leftRight = c.x + offset;
		// Check edge cases of the neighbour
		if (leftRight >= 0 && leftRight < width)
			if (!grid[leftRight][c.y].hasBeenVisited())
				return true;

		const int &upDown = c.y + offset;
		if (upDown >= 0 && upDown < height)
			if (!grid[c.x][upDown].hasBeenVisited())
				return true;
	}
	return false;
}

Cell& Maze::getRandomUnvisitedNeighbour(const Cell &c) {
	std::vector<std::reference_wrapper<Cell>> unvisitedNeighbours;

	for (int offset : {-1, 1}) {

		const int &leftRight = c.x + offset;
		if (leftRight >= 0 && c.y >= 0 && leftRight < width && c.y < height) {
			Cell &neighbour = grid[leftRight][c.y];

			if (!neighbour.hasBeenVisited())
				unvisitedNeighbours.push_back(neighbour);
		}

		const int &upDown = c.y + offset;
		if (c.x >= 0 && upDown >= 0 && c.x < width && upDown < height) {
			Cell &neighbour = grid[c.x][upDown];

			if (!neighbour.hasBeenVisited())
				unvisitedNeighbours.push_back(neighbour);
		}
	}
	return unvisitedNeighbours[rand() % unvisitedNeighbours.size()];
}

void Maze::removeWalls(Cell &c1, Cell &c2) {
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