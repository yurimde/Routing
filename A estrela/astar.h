#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>
#include <map>
#include "cell.h"

std::vector<Cell*> findPath(Cell* start, Cell* end, std::vector<std::vector<Cell>>& map, const std::vector<std::vector<Cell*>>& paths);
double heuristic(Cell* a, Cell* b);
bool isCellInAnyPath(Cell* cell, const std::vector<std::vector<Cell*>>& paths);
std::vector<std::vector<Cell*>> findPathsForPairs(const std::vector<std::pair<Cell, Cell>>& startEndPairs, std::vector<std::vector<Cell>>& map);

#endif
