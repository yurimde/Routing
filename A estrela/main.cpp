#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

// Definição das dimensões do mapa
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 25;

// Definição da estrutura de cada célula no mapa
struct Cell {
    int x, y; // Posição da célula
    bool isFree; // Se a célula está livre ou não
    int isVisited = 0;
    double gCost; // Custo acumulado do ponto inicial até esta célula
    double hCost; // Custo estimado da célula até o ponto final
    Cell* parent; // Ponteiro para a célula predecessora no caminho

    Cell(int x, int y, bool isFree) : x(x), y(y), isFree(isFree), isVisited(false), gCost(0.0), hCost(0.0), parent(nullptr) {}

    // Função para calcular o custo total (fCost)
    double fCost() const {
        return gCost + hCost;
    }
};

// Criando o mapa
std::vector<std::vector<Cell>> map(MAP_HEIGHT, std::vector<Cell>(MAP_WIDTH, Cell(0, 0, true)));
void initializeMap() {
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            // Inicializa todas as células como livres
            map[i][j].isFree = true;
            map[i][j].x = j; // Define a coordenada x da célula
            map[i][j].y = i; // Define a coordenada y da célula
            map[i][j].isVisited = false;
            // Define obstáculos nas colunas 4 e 19 entre as linhas 4 e 19
            if ((j >= 19 && j <=21) && i >= 4 && i <= 19) {
                map[i][j].isFree = false;
            }
        }
    }
}

// Função de heurística (distância de Manhattan)
double heuristic(Cell* a, Cell* b) {
    double euclideanDist = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
    //std::cout << "Distancia da celula (" << a->x << "," << b->x << "): " << euclideanDist << std::endl;
    return euclideanDist;
}

// Função para verificar se uma célula está em algum caminho existente
bool isCellInAnyPath(Cell* cell, const std::vector<std::vector<Cell*>>& paths) {
    for (const auto& path : paths) {
        if (std::find(path.begin(), path.end(), cell) != path.end()) {
            return true;
        }
    }
    return false;
}

// Função para encontrar o caminho usando o algoritmo A*
std::vector<Cell*> findPath(Cell* start, Cell* end, std::vector<std::vector<Cell>>& map, const std::vector<std::vector<Cell*>>& paths) {
    std::vector<Cell*> path;

    // Verifica se os pontos inicial e final estão dentro dos limites do mapa e se são células válidas
    if (!start || !end || !start->isFree || !end->isFree) {
        std::cout << "Pontos de início ou fim inválidos." << std::endl;
        return path;
    }

    // Lista de células abertas e fechadas
    std::vector<Cell*> openList;
    std::vector<Cell*> closedList;

    openList.push_back(start);
    int count = 0;
    while (!openList.empty()) {
        // Encontrar a célula com o menor custo f
        double minCost = NULL;
        int index_temp = 0;
        for (size_t i = 1; i < openList.size(); ++i) {
            if (minCost == NULL) {
                minCost = openList[i]->fCost();
                index_temp = i;
            } else if (openList[i]->fCost() < minCost) {
                minCost = openList[i]->fCost();
                index_temp = i;
            }
        }
        Cell* currentCell = openList[index_temp];

        // Remover a célula atual da lista aberta e adicioná-la à lista fechada
        openList.erase(std::remove(openList.begin(), openList.end(), currentCell), openList.end());
        closedList.push_back(currentCell);
        currentCell->isVisited = currentCell->hCost;

        // Se chegamos ao ponto final, reconstroi o caminho
        if (currentCell->x == end->x && currentCell->y == end->y) {
            Cell* temp = currentCell;
            while (temp != start) {
                path.push_back(temp);
                temp = temp->parent;
            }
            std::reverse(path.begin(), path.end());
            break;
        }

        // Gera os vizinhos da célula atual
        for (int xOffset = -1; xOffset <= 1; ++xOffset) {
            for (int yOffset = -1; yOffset <= 1; ++yOffset) {
                // Ignora a própria célula atual
                if ((xOffset == 0 && yOffset == 0) || (xOffset != 0 && yOffset != 0)) {
                    continue;
                }

                int checkX = currentCell->x + xOffset;
                int checkY = currentCell->y + yOffset;

                // Verifica se o vizinho está dentro dos limites do mapa
                if (checkX >= 0 && checkX < MAP_WIDTH && checkY >= 0 && checkY < MAP_HEIGHT) {
                    Cell* neighbor = &map[checkY][checkX];

                    // Verifica se o vizinho não está na lista fechada ou é uma célula ocupada
                    if (std::find(closedList.begin(), closedList.end(), neighbor) == closedList.end() &&
                        neighbor->isFree && !isCellInAnyPath(neighbor, paths)) { // Verifica se a célula não está em nenhum caminho existente
                        double newCost = currentCell->fCost() + 1;

                        // Se o vizinho não está na lista aberta ou tem um custo menor que o custo atual
                        if (newCost < neighbor->fCost() || std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                            neighbor->gCost = currentCell->gCost + 1;
                            neighbor->hCost = heuristic(neighbor, end);
                            neighbor->parent = currentCell;

                            // Se o vizinho não está na lista aberta, adiciona-o
                            if (std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                                openList.push_back(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }

    return path;
}



// Nova função para calcular caminhos para múltiplos pontos de início e fim
std::vector<std::vector<Cell*>> findPathsForPairs(const std::vector<std::pair<Cell, Cell>>& startEndPairs, std::vector<std::vector<Cell>>& map) {
    std::vector<std::vector<Cell*>> allPaths;

    for (const auto& pair : startEndPairs) {
        Cell* start = &map[pair.first.y][pair.first.x];
        Cell* end = &map[pair.second.y][pair.second.x];

        // Encontrando o caminho
        std::vector<Cell*> path = findPath(start, end, map, allPaths);

        // Exibindo o caminho encontrado
        if (path.empty()) {
            std::cout << "Caminho nao encontrado para o par (" << start->x << ", " << start->y << ") -> (" << end->x << ", " << end->y << ")." << std::endl;
        } else {
            std::cout << "Caminho encontrado para o par (" << start->x << ", " << start->y << ") -> (" << end->x << ", " << end->y << "):" << std::endl;
            for (Cell* cell : path) {
                std::cout << "(" << cell->x << ", " << cell->y << ") ";
            }
            std::cout << std::endl;

            // Adicionando o caminho à lista de caminhos existentes
            allPaths.push_back(path);
        }
    }

    return allPaths;
}




// Função para imprimir o mapa com os caminhos destacados
void printMap(const std::vector<std::vector<Cell>>& map, const std::vector<std::vector<Cell*>>& paths) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            bool isPath = false;

            // Verifica se a célula está em algum caminho
            for (size_t i = 0; i < paths.size(); ++i) {
                const auto& path = paths[i];
                if (std::find_if(path.begin(), path.end(), [x, y](const Cell* cell) {
                        return cell->x == x && cell->y == y;
                    }) != path.end()) {
                    isPath = true;

                    // Imprime o caractere de caminho com uma cor diferente para cada caminho
                    std::cout << "\033[1;" << 31 + i << "m* \033[0m";
                    break;
                }
            }

            if (!isPath) {
                /*if (map[y][x].isVisited > 0) {
                    std::cout << int(map[y][x].fCost()) << " ";
                } else*/ if (map[y][x].isFree) {
                    std::cout << ". "; // Caractere para célula livre
                } else {
                    std::cout << "# "; // Caractere para obstáculo
                }
            }
        }
        std::cout << std::endl;
    }
}


int main() {
    initializeMap();

    // Definindo pontos de início e fim para múltiplos caminhos
    std::vector<std::pair<Cell, Cell>> startEndPairs = {
        {{15, 15, true}, {35, 18, true}},
        {{8, 24, true}, {35, 8, true}},
        {{5, 5, true}, {30, 12, true}},
        {{10, 20, true}, {25, 5, true}},
        
       
        {{10, 5, true}, {25, 16, true}},
        
};

    // Encontrando caminhos para os pares de pontos
    std::vector<std::vector<Cell*>> allPaths = findPathsForPairs(startEndPairs, map);

    // Exibindo o mapa com os caminhos destacados
    std::cout << "\nMapa com os caminhos destacados:" << std::endl;
    printMap(map, allPaths);

    return 0;
}