#ifndef PATH_FINDING_ALGO_H
#define PATH_FINDING_ALGO_H

#include "mainFrame.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

std::tuple<int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(int source[2], int target[2], int gridRow, int gridCol, MainFrame *mainFramePtr);

#endif // PATH_FINDING_ALGO_H