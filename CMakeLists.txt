cmake_minimum_required(VERSION 3.10)
project(CS170Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS170Project1 main.cpp
        Problem.cpp
        Problem.h
        Puzzle.h
        Tree.h
        Frontier.h
        frontiers/BreadthFirstSearch.h
        frontiers/UniformCostSearch.h
        frontiers/AStarMisplacedTile.h
        frontiers/AStarEuclidean.h)
