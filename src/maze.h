#pragma once

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int MAZE_DIMENSION = 30;
const int X = 0;
const int Y = 1;

enum MAP_STATE{
    WALL,
    PATH
};

class Cell{
    public:
    MAP_STATE _state;   /* determines whether the cell is a WALL or a PATH*/
    int _index[2];  /* array which contains the xy position of the cell in the matrix */
    Cell(int i, int j){
        _state = WALL;
        _index[0] = i;
        _index[1] = j;
    }
    /**
     * Gets the cell's neighbors that are a distance of 2 away
     * 
     * @param std::vector<std::vector<Cell*>> the maze matrix
     * @return a vector containing all of the valid neighbor cells
    */
    std::vector<Cell*> getNeighbors(std::vector<std::vector<Cell*>>);
};

class Maze{
    public:
    std::vector<std::vector<Cell*>> grid;   /* 2D matrix simulating the maze */
    std::vector<Cell*> frontier;    /* vector containing all of the added frontiers through Prim's algorithm */
    int _numWalls;  /* total number of walls in the maze */
    int _numFloors; /* total number of floors in the maze */
    int _spawnX;
    int _spawnZ;
    Maze(){
        _numFloors = 0;
        _numWalls = 900;
        this->frontier = std::vector<Cell*>();
        for(int i = 0; i < MAZE_DIMENSION; ++i){
            this->grid.push_back(std::vector<Cell*>());
            for(int j = 0; j < MAZE_DIMENSION; ++j){
                this->grid[i].push_back(new Cell(i,j));
            }
        srand(time(NULL));
        }
        primsAlgorithm();
        addBoundaries();
    }
    /**
     * Checks to see if a position in maze is valid to be added to the frontier
     * 
     * @param int x position in the matrix
     * @param int y position in the matrix
     * @return true if valid false if not
    */
    bool checkFrontier(int,int);
    
    /**
     * For the current frontier, check each 2-distant space in each direction and add that space to the frontier list if it is
     * in bounds, not already in the frontier list, and has WALL state
     * 
     * @param Cell* the current cell being processed in the maze 
    */
    void addFrontiers(Cell*);

    /**
     * Connects a path from the selected neighbor cell to the frontier cell
     * 
     * @param Cell* the frontier cell
     * @param Cell* the neighbor cell
    */
    void connectFrontiers(Cell*, Cell*);

    /**
     * The randomized Prim's algorithm used for creating random-generated mazes 
    */
    void primsAlgorithm();

    /**
     * Checks to see if a new cell prospect has already been added to the frontier list to prevent duplication
     * 
     * @param Cell* a cell in the matrix being checked for presence in the frontier
     * @return true if in the frontier false if not 
    */
    bool inFrontier(Cell*);

    /**
     * Decrements the amount of walls and increments the amount of floors after state changes
    */
    void updateWallCount();

    /**
     * Ensures the maze is wrapped in a rectangle of walls; if any floors found in the outer ring, add another line of walls in that direction
    */
    void addBoundaries();

    /**
     * Checks to see if either the top-most or bottom-most row consists of only walls
     * 
     * @param std::vector<Cell*> the row being checked
     * @return true if floors are present in the row false if only walls
    */
    bool checkHoriBoundary(std::vector<Cell*>);

    /**
     * Checks to see if either the left-most or right-most column consists of only walls
     * 
     * @param int the index of the column to be checked (0 or size-1)
     * @return true if floors are present in the row false if only walls
    */
    bool checkVertBoundary(int);

    /**
     * returns the cell state
     * 
     * @param int x position in matrix
     * @param int y position in matrix
     * @return WALL or PATH
    */
    MAP_STATE getState(int,int);
};
#endif