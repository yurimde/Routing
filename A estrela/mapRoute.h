#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>
#include <map>
#include "cell.h"
#include <sstream>
#include <string>
// Definição das dimensões do mapa



std::vector<std::vector<Cell>> initializeMap();
void printMap(const std::vector<std::vector<Cell>>& map, const std::vector<std::vector<Cell*>>& paths, const std::vector<std::string>& pathColors);
std::vector<std::pair<Cell, Cell>> readInputPoints(const std::string& filename, std::vector<std::string>& pathColors);

#endif
