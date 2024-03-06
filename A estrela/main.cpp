#include <iostream>
#include "astar.h"
#include "mapRoute.h"

int main() {
    std::vector<std::vector<Cell>> map = initializeMap();
    
    std::vector<std::string> pathColors;
    
    // Inicializa o mapa e lê os pontos de entrada
    std::vector<std::pair<Cell, Cell>> startEndPairs = readInputPoints("input_points.txt", pathColors);
    std::cout << "Testemain" << std::endl;
    std::vector<std::vector<Cell*>> allPaths = findPathsForPairs(startEndPairs, map);

    // Exibe o mapa com os caminhos destacados
    std::cout << "\nMapa com os caminhos destacados:" << std::endl;
    printMap(map, allPaths, pathColors);

    return 0;
}
