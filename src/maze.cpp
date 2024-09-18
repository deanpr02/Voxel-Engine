#include "maze.h"

std::vector<Cell*> Cell::getNeighbors(std::vector<std::vector<Cell*>> grid){
    std::vector<Cell*> neighbors = std::vector<Cell*>();
    int x = _index[X];
    int y = _index[Y];
    //checks if space to the left is valid and a path, if yes then push it into the neighbors vector
    if(x-2 >= 0 && grid[x-2][y]->_state == PATH){
        neighbors.push_back(grid[x-2][y]);
    }
    //checks if space to the right is valid and a path, if yes then push it into the neighbors vector
    if(x+2 < grid.size() && grid[x+2][y]->_state == PATH){
        neighbors.push_back(grid[x+2][y]);
    }
    //checks if space below is valid and a path, if yes then push it into the neighbors vector
    if(y-2 >= 0 && grid[x][y-2]->_state == PATH){
        neighbors.push_back(grid[x][y-2]);
    }
    //checks if space above is valid and a path, if yes then push it into the neighbors vector
    if(y+2 < grid.size() && grid[x][y+2]->_state == PATH){
        neighbors.push_back(grid[x][y+2]);
    }
    return neighbors;
}


bool Maze::inFrontier(Cell* cell){
    //loops over the frontier to see if the cell we are checking is already present in it to avoid duplicate cells
    for(int i = 0; i < this->frontier.size(); ++i){
        if(this->frontier[i] == cell){
            return true;
        }
    }
    return false;
}

bool Maze::checkFrontier(int x, int y){
    if(x < 0 || x >= this->grid.size()){
        return false;
    }
    if(y < 0 || y >= this->grid.size()){
        return false;
    }
    if(!inFrontier(this->grid[x][y]) && this->grid[x][y]->_state == WALL){
        return true;
    }
    return false;
}

void Maze::addFrontiers(Cell* cell){
    int x = cell->_index[X];
    int y = cell->_index[Y];
    if(checkFrontier(x-2,y)) this->frontier.push_back(this->grid[x-2][y]);
    if(checkFrontier(x+2,y)) this->frontier.push_back(this->grid[x+2][y]);
    if(checkFrontier(x,y-2)) this->frontier.push_back(this->grid[x][y-2]);
    if(checkFrontier(x,y+2)) this->frontier.push_back(this->grid[x][y+2]);
}

void Maze::connectFrontiers(Cell* src, Cell* dst){
    int src_x = src->_index[X];
    int src_y = src->_index[Y];
    int dst_x = dst->_index[X];
    int dst_y = dst->_index[Y];
    if(src_x < dst_x){
        this->grid[src_x+1][src_y]->_state = PATH;
        updateWallCount();
    }
    if(src_x > dst_x){
        this->grid[src_x-1][src_y]->_state = PATH;
        updateWallCount();
    }   
    if(src_y < dst_y){
        this->grid[src_x][src_y+1]->_state = PATH;
        updateWallCount();
    }
    if(src_y > dst_y){
        this->grid[src_x][src_y-1]->_state = PATH;
        updateWallCount();
    }
}
//random function: rand() % (65 + 1 - 0) + 0
void Maze::primsAlgorithm(){
    int prims_index = 0;
    int rand_x = rand() % (MAZE_DIMENSION);
    int rand_y = rand() % (MAZE_DIMENSION);
    _spawnX = rand_x;
    _spawnZ = rand_y;
    this->frontier.push_back(this->grid[rand_x][rand_y]);
    while(this->frontier.size() > 0){
        Cell* cell = this->frontier[prims_index];
        cell->_state = PATH;
        updateWallCount();
        addFrontiers(cell);
        std::vector<Cell*> neighbors = cell->getNeighbors(this->grid);
        if(neighbors.size() > 0){
            int rand_i = rand() % ((neighbors.size()));
            Cell* neighbor = neighbors[rand_i];
            connectFrontiers(cell,neighbor);
            addFrontiers(neighbor);
        }
        this->frontier.erase(this->frontier.begin()+prims_index);
        prims_index = this->frontier.size() > 0 ? rand() % ((this->frontier.size())) : 0;
    }
}

MAP_STATE Maze::getState(int i, int j){
    return grid[i][j]->_state;
}

void Maze::updateWallCount(){
    _numFloors += 1;
    _numWalls -= 1;
}

bool Maze::checkHoriBoundary(std::vector<Cell*> row){
    for(int i=0;i<row.size();++i){
        if(row[i]->_state == 1){
            return true;
        }
    }
    return false;
}

bool Maze::checkVertBoundary(int index){
    for(int i=0;i<grid.size();++i){
        if(grid[i][index]->_state == 1){
            return true;
        }
    }
    return false;
}


void Maze::addBoundaries(){
    std::vector<Cell*> temp = std::vector<Cell*>();
    for(int i=0; i<MAZE_DIMENSION;++i){
            temp.push_back(new Cell(-1,-1));
        }
    if(checkHoriBoundary(grid[0])){
        //add to top
        grid.insert(grid.begin(),temp);
        _numWalls += MAZE_DIMENSION;
    }
    if(checkHoriBoundary(grid[grid.size()-1])){
        //add to bottom
        grid.push_back(temp);
        _numWalls += MAZE_DIMENSION;
    }
    if(checkVertBoundary(0)){
        //add to left
        for(int j=0;j<grid.size();++j){
            grid[j].insert(grid[j].begin(),new Cell(-1,-1));
            _numWalls += 1;
            //std::cout<<"ok";
        }
    }
    if(checkVertBoundary(grid[0].size()-1)){
        //add to right
        for(int j=0;j<grid.size();++j){
            grid[j].push_back(new Cell(-1,-1));
            _numWalls += 1;
        }
    }

}
