#include "mapRoute.h"



Cell::Cell(int x, int y, bool isFree) : x(x), y(y), isFree(isFree), isVisited(false), gCost(0.0), hCost(0.0), parent(nullptr) {}

double Cell::fCost() const {
    return gCost + hCost;
}



std::vector<std::vector<Cell>> initializeMap() {
    std::vector<std::vector<Cell>> map(MAP_HEIGHT, std::vector<Cell>(MAP_WIDTH, Cell(0, 0, true)));

    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            map[i][j].isFree = true;
            map[i][j].x = j;
            map[i][j].y = i;
            map[i][j].isVisited = false;
            if ((j >= 19 && j <=21) && i >= 4 && i <= 19) {
                map[i][j].isFree = false;
            }
        }
    }

    return map;
}

std::map<std::string, std::string> colorMap = {
    {"red", "\x1b[31m"},
    {"green", "\x1b[32m"},
    {"yellow", "\x1b[33m"},
    {"blue", "\x1b[34m"},
    {"magenta", "\x1b[35m"},
    {"cyan", "\x1b[36m"},
    {"reset", "\x1b[0m"}
};

void printMap(const std::vector<std::vector<Cell>>& map, const std::vector<std::vector<Cell*>>& paths, const std::vector<std::string>& pathColors) {
    int pathNumber = 1;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            bool isPath = false;

            for (size_t i = 0; i < paths.size(); ++i) {
                const auto& path = paths[i];
                if (std::find_if(path.begin(), path.end(), [x, y](const Cell* cell) {
                        return cell->x == x && cell->y == y;
                    }) != path.end()) {
                    isPath = true;

                    std::cout << colorMap[pathColors[i]] << pathNumber+i << " " << colorMap["reset"];
                    break;
                }
            }

            if (!isPath) {
                if (map[y][x].isFree) {
                    std::cout << ". ";
                } else {
                    std::cout << "# ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void shuffleInputPoints(std::vector<std::pair<Cell, Cell>>& startEndPairs, std::vector<std::string>& pathColors) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(startEndPairs.begin(), startEndPairs.end(), g);
    std::shuffle(pathColors.begin(), pathColors.end(), g);
}

std::vector<std::pair<Cell, Cell>> readInputPoints(const std::string& filename, std::vector<std::string>& pathColors) {
    std::vector<std::pair<Cell, Cell>> startEndPairs;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return startEndPairs;
    }else{
        std::cout << "Arquivo aberto" << std::endl;}

    
    
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << "Teste1" << std::endl;
        std::istringstream iss(line);
        int startX, startY, endX, endY;
        std::string color;

        if (!(iss >> startX >> startY >> endX >> endY >> color)) {
            std::cerr << "Erro ao ler linha do arquivo" << std::endl;
            break;
        }else{
            Cell startCell(startX, startY, true);
            Cell endCell(endX, endY, true);
            startEndPairs.push_back(std::make_pair(startCell, endCell));
            pathColors.push_back(color);

            std::cout << "Teste2" << std::endl;
        }

        
    }
    std::cout << "Teste3" << std::endl;
    inputFile.close();

    // Embaralhar os pontos de entrada
    shuffleInputPoints(startEndPairs, pathColors);

    return startEndPairs;
}
