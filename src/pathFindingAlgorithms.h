#ifndef PATH_FINDING_ALGO_H
#define PATH_FINDING_ALGO_H

#include "mainFrame.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

// return: numOfCellsVisited, minTravelCost, prev
std::tuple<int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr);

#endif // PATH_FINDING_ALGO_H