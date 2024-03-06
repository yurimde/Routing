#include "astar.h"

std::vector<Cell*> findPath(Cell* start, Cell* end, std::vector<std::vector<Cell>>& map, const std::vector<std::vector<Cell*>>& paths) {
    std::vector<Cell*> path;

    if (!start || !end || !start->isFree || !end->isFree) {
        std::cout << "Pontos de início ou fim inválidos." << std::endl;
        return path;
    }

    std::vector<Cell*> openList;
    std::vector<Cell*> closedList;

    openList.push_back(start);

    while (!openList.empty()) {
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

        openList.erase(std::remove(openList.begin(), openList.end(), currentCell), openList.end());
        closedList.push_back(currentCell);
        currentCell->isVisited = currentCell->hCost;

        if (currentCell->x == end->x && currentCell->y == end->y) {
            Cell* temp = currentCell;
            while (temp != start) {
                path.push_back(temp);
                temp = temp->parent;
            }
            std::reverse(path.begin(), path.end());
            break;
        }

        for (int xOffset = -1; xOffset <= 1; ++xOffset) {
            for (int yOffset = -1; yOffset <= 1; ++yOffset) {
                if ((xOffset == 0 && yOffset == 0) || (xOffset != 0 && yOffset != 0)) {
                    continue;
                }

                int checkX = currentCell->x + xOffset;
                int checkY = currentCell->y + yOffset;

                if (checkX >= 0 && checkX < MAP_WIDTH && checkY >= 0 && checkY < MAP_HEIGHT) {
                    Cell* neighbor = &map[checkY][checkX];

                    if (std::find(closedList.begin(), closedList.end(), neighbor) == closedList.end() &&
                        neighbor->isFree && !isCellInAnyPath(neighbor, paths)) {
                        double newCost = currentCell->fCost() + 1;

                        if (newCost < neighbor->fCost() || std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                            neighbor->gCost = currentCell->gCost + 1;
                            neighbor->hCost = heuristic(neighbor, end);
                            neighbor->parent = currentCell;

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

double heuristic(Cell* a, Cell* b) {
    double euclideanDist = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
    return euclideanDist;
}

bool isCellInAnyPath(Cell* cell, const std::vector<std::vector<Cell*>>& paths) {
    for (const auto& path : paths) {
        if (std::find(path.begin(), path.end(), cell) != path.end()) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<Cell*>> findPathsForPairs(const std::vector<std::pair<Cell, Cell>>& startEndPairs, std::vector<std::vector<Cell>>& map) {
    std::vector<std::vector<Cell*>> allPaths;

    for (const auto& pair : startEndPairs) {
        Cell* start = &map[pair.first.y][pair.first.x];
        Cell* end = &map[pair.second.y][pair.second.x];

        std::vector<Cell*> path = findPath(start, end, map, allPaths);

        if (path.empty()) {
            std::cout << "Caminho nao encontrado para o par (" << start->x << ", " << start->y << ") -> (" << end->x << ", " << end->y << ")." << std::endl;
        } else {
            std::cout << "Caminho encontrado para o par (" << start->x << ", " << start->y << ") -> (" << end->x << ", " << end->y << "):" << std::endl;
            for (Cell* cell : path) {
                std::cout << "(" << cell->x << ", " << cell->y << ") ";
            }
            std::cout << std::endl;

            allPaths.push_back(path);
        }
    }

    return allPaths;
}