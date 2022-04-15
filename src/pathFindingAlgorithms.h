#ifndef PATH_FINDING_ALGO_H
#define PATH_FINDING_ALGO_H

#include "mainFrame.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

// return: numOfCellsVisited, frequencyOfCellChecking, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr);

// return: numOfCellsVisited, frequencyOfCellChecking, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> aStarSearch(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr);

// return: manhattan distance
int getManhattanDistance(std::array<int, 2> currentCell, std::array<int, 2> targetCell);

#endif // PATH_FINDING_ALGO_H