#include "heuristicFunctions.h"

int getManhattanDistance(std::array<int, 2> currentCell, std::array<int, 2> targetCell)
{
    return abs(targetCell[1] - currentCell[1]) + abs(targetCell[0] - currentCell[0]);
}