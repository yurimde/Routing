#ifndef CELL_H
#define CELL_H


const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 25;

struct Cell {
    int x, y;
    bool isFree;
    int isVisited;
    double gCost;
    double hCost;
    Cell* parent;

    Cell(int x, int y, bool isFree);

    double fCost() const;
};

#endif // CELL_H