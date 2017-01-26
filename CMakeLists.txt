cmake_minimum_required(VERSION 2.8)
project(maze_generator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Cell.cpp Cell.hpp Maze.cpp Maze.hpp AStar.cpp AStar.hpp Node.cpp Node.hpp)
add_executable(maze_generator ${SOURCE_FILES})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(maze_generator SDL2 SDL2pp)