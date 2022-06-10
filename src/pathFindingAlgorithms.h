#ifndef PATH_FINDING_ALGO_H
#define PATH_FINDING_ALGO_H

#include "mainFrame.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <array>

// return: numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation=false);

// return: numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> aStarSearch(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation=false);

// return: numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> greedyBestFirstSearch(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation=false);

// return: numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> bfs(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation=false);

// return: numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost, prev
std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> bidirectionalBFS(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation=false);

#endif // PATH_FINDING_ALGO_H