#include <iostream>
#include <queue>
#include <vector>

struct Cell {
    int x, y;
    bool isFree;
    Cell* parent;

    Cell() : x(0), y(0), isFree(true), parent(nullptr){}

    Cell(int x, int y, bool isFree) : x(x), y(y), isFree(isFree), parent(nullptr) {}
};

const int MAP_WIDTH = 25;
const int MAP_HEIGHT = 25;

std::vector<std::vector<Cell>> map(MAP_HEIGHT, std::vector<Cell>(MAP_WIDTH));

void initializeMap() {
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            map[i][j].isFree = true;
            map[i][j].x = j;
            map[i][j].y = i;

            // Definindo obstáculos nas colunas 4 e 19 entre as linhas 4 e 19
            if ((j >= 0 && j <=8 || j >= 15 && j <=19) && i >= 4 && i <= 19) {
                map[i][j].isFree = false;
            }
        }
    }
}

std::vector<Cell*> findPath(Cell* start, Cell* end) {
    std::queue<Cell*> q;
    q.push(start);

    while (!q.empty()) {
        Cell* current = q.front();
        q.pop();

        std::cout << "Current Cell: (" << current->x << "," << current->y << ")" << std::endl;

        if (current->x == end->x && current->y == end->y) {
            std::vector<Cell*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        // Movimentos possíveis: acima, abaixo, esquerda e direita
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX].isFree) {
                Cell* neighbor = &map[newY][newX];
                if (neighbor->parent == nullptr) {
                    neighbor->parent = current;
                    q.push(neighbor);
                }
            }
        }
    }

    return {}; // Caminho não encontrado
}



void printMap(const std::vector<std::vector<Cell>>& map, const std::vector<Cell*>& path) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            bool isPath = false;

            // Verifica se a célula está no caminho
            for (Cell* cell : path) {
                if (cell->x == x && cell->y == y) {
                    isPath = true;
                    break;
                }
            }

            if (isPath) {
                std::cout << "* "; // Caractere para o caminho percorrido
            } else if (map[y][x].isFree) {
                std::cout << ". "; // Caractere para célula livre
            } else {
                std::cout << "# "; // Caractere para obstáculo
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    initializeMap();

    Cell startCell(0,0,true);
    Cell endCell(24,24,true);

    std::vector<Cell*> path = findPath(&startCell, &endCell);

    if (path.empty()) {
        std::cout << "Caminho não encontrado." << std::endl;
    } else {
        std::cout << "Caminho encontrado:" << std::endl;
        printMap(map, path);
    }

    return 0;
}
