#include "pathFindingAlgorithms.h"

#include <wx/wx.h>

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

typedef std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> MinHeap;

std::tuple<int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(int source[2], int target[2], int gridRow, int gridCol, MainFrame *mainFramePtr)
{
    wxGrid *gridPtr = mainFramePtr->m_lp->grid;

    // VARIABLLE DECLARATION
    std::vector<std::vector<int>> minTravelCost(gridRow, std::vector<int>(gridCol, INT_MAX));
    std::vector<std::vector<std::array<int, 2>>> prev(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<int>> visited(gridRow, std::vector<int>(gridCol, false));

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int pointExplored = 0;

    // BASE CASE
    minTravelCost[source[0]][source[1]] = 0;

    MinHeap minHeap;
    minHeap.push({0, source[0], source[1]}); // {effort, r, c}

    while (!minHeap.empty())
    {
        auto topEle = minHeap.top();
        int curTravelCost = topEle[0];
        int curR = topEle[1];
        int curC = topEle[2];
        minHeap.pop();

        if (curR == target[0] && curC == target[1])
        {
            // paint it back to red
            gridPtr->SetCellBackgroundColour(curR, curC, wxColour(255, 0, 0)); // red
            gridPtr->ForceRefresh();
            break;
        }
        if (visited[curR][curC])
        {
            continue;
        }
        visited[curR][curC] = true;

        for (auto move : moves)
        {
            int newR = curR + move[0];
            int newC = curC + move[1];

            if (newR < 0 || newR >= gridRow || newC < 0 || newC >= gridCol)
            {
                continue;
            }

            if (visited[newR][newC])
            {
                continue;
            }

            // skip if it is a wall
            if (gridPtr->GetCellBackgroundColour(newR, newC) == wxColor(0, 0, 0))
            {
                continue;
            }

            pointExplored++;

            int newTravelCost = curTravelCost + 1;
            if (newTravelCost < minTravelCost[newR][newC])
            {
                minTravelCost[newR][newC] = newTravelCost;
                prev[newR][newC] = {curR, curC};
                minHeap.push({newTravelCost, newR, newC});

                gridPtr->SetCellBackgroundColour(newR, newC, wxColour(0, 0, 255)); // blue
                gridPtr->ForceRefresh();
            }
        }
        // wxMilliSleep(10);
        gridPtr->ForceRefresh();
    }
    return {pointExplored, minTravelCost[target[0]][target[1]], prev};
}