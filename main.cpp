#include <SDL2pp/SDL2pp.hh>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Maze.hpp"
#include "AStar.hpp"

using namespace SDL2pp;

int main() {
	srand(static_cast<unsigned int>(time(0)));
	SDL sdl(SDL_INIT_VIDEO);
	Window gWindow("Maze generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	Renderer gRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Maze maze{40, 40};
	// Maze maze{"myMaze.txt"};
	// grid.reset(20, 20);
	maze.generate(0, 0);
	// grid.importFromFile("myMaze.txt");
	// grid.exportToFile("myMaze.txt");
	std::clog << maze;

	// AStar a(40, 40);
	AStar a(maze);
	a.resolve(0, 0, 39, 39);


	gRenderer.SetDrawColor(255, 255, 255);
	gRenderer.Clear();

	maze.draw(gRenderer, 20);
	a.draw(gRenderer, 20);

	gRenderer.Present();


	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT)
				break;

		SDL_Delay(10);
	}
	return 0;
}