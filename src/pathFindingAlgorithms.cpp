#include "pathFindingAlgorithms.h"

#include <wx/wx.h>

#include <array>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

typedef std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> MinHeap;

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr)
{
    wxGrid *gridPtr = mainFramePtr->m_lp->grid;

    // VARIABLLE DECLARATION
    std::vector<std::vector<int>> minTravelCost(gridRow, std::vector<int>(gridCol, INT_MAX));
    std::vector<std::vector<std::array<int, 2>>> prev(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<int>> visited(gridRow, std::vector<int>(gridCol, false));

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int numOfCellsVisited = 0;
    int numOfCellCheckingOccurrence = 0;
    bool foundTarget = false; // not used as it violates Dijkstra's Algorithm

    // BASE CASE
    minTravelCost[source[0]][source[1]] = 0;

    MinHeap minHeap;
    minHeap.push({0, source[0], source[1]}); // {travelCost, r, c}

    while (!minHeap.empty() && !foundTarget)
    {
        auto topEle = minHeap.top();
        int curTravelCost = topEle[0];
        int curR = topEle[1];
        int curC = topEle[2];
        minHeap.pop();

        if (visited[curR][curC])
        {
            continue;
        }

        visited[curR][curC] = true;
        numOfCellsVisited++;

        // target cell being popped from minHeap means its travel cost is minimum now
        if (curR == target[0] && curC == target[1])
        {
            break;
        }

        gridPtr->SetCellBackgroundColour(curR, curC, wxColour(0, 0, 125)); // dark blue

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

            numOfCellCheckingOccurrence++;
            gridPtr->SetCellBackgroundColour(newR, newC, wxColour(0, 0, 255)); // blue

            int newTravelCost = curTravelCost + 1;
            if (newTravelCost < minTravelCost[newR][newC])
            {
                minTravelCost[newR][newC] = newTravelCost;
                prev[newR][newC] = {curR, curC};
                minHeap.push({newTravelCost, newR, newC});

                /*
                    This is a kind of optimization as the travel cost from
                    one cell to another cell in a grid is always one.
                    But if the travel cost is different, we can't do this.
                */
                // if (newR == target[0] && newC == target[1])
                // {
                //     foundTarget = true;
                //     break;
                // }
            }
        }
        // wxMilliSleep(10);
        gridPtr->ForceRefresh();
    }

    // paint the destination point back to red
    gridPtr->SetCellBackgroundColour(target[0], target[1], wxColour(255, 0, 0)); // red
    gridPtr->ForceRefresh();

    return {numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost[target[0]][target[1]], prev};
}

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> aStarSearch(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr)
{
    wxGrid *gridPtr = mainFramePtr->m_lp->grid;

    // VARIABLLE DECLARATION
    std::vector<std::vector<int>> minTravelCost(gridRow, std::vector<int>(gridCol, INT_MAX));
    std::vector<std::vector<int>> distanceTravelled(gridRow, std::vector<int>(gridCol, INT_MAX));
    std::vector<std::vector<std::array<int, 2>>> prev(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<int>> visited(gridRow, std::vector<int>(gridCol, false));

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int numOfCellsVisited = 0;
    int numOfCellCheckingOccurrence = 0;

    // BASE CASE
    minTravelCost[source[0]][source[1]] = 0;
    distanceTravelled[source[0]][source[1]] = 0;

    MinHeap minHeap;
    minHeap.push({0+getManhattanDistance(source, target), source[0], source[1]}); // {travelCost, r, c}

    while (!minHeap.empty())
    {
        auto topEle = minHeap.top();
        int curTravelCost = topEle[0];
        int curR = topEle[1];
        int curC = topEle[2];
        minHeap.pop();

        if (visited[curR][curC])
        {
            continue;
        }

        visited[curR][curC] = true;
        numOfCellsVisited++;

        // target cell being popped from minHeap means its travel cost is minimum now
        if (curR == target[0] && curC == target[1])
        {
            break;
        }

        gridPtr->SetCellBackgroundColour(curR, curC, wxColour(0, 0, 125)); // dark blue

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

            numOfCellCheckingOccurrence++;
            gridPtr->SetCellBackgroundColour(newR, newC, wxColour(0, 0, 255)); // blue

            int newDistanceTravelled = distanceTravelled[curR][curC] + 1;
            int newTravelCost = newDistanceTravelled + getManhattanDistance({newR, newC}, target);
            
            if (newDistanceTravelled < distanceTravelled[newR][newC])
            {
                distanceTravelled[newR][newC] = newDistanceTravelled;
            }

            if (newTravelCost < minTravelCost[newR][newC])
            {
                minTravelCost[newR][newC] = newTravelCost;
                prev[newR][newC] = {curR, curC};
                minHeap.push({newTravelCost, newR, newC});
            }
        }
        // wxMilliSleep(10);
        gridPtr->ForceRefresh();
    }

    // paint the destination point back to red
    gridPtr->SetCellBackgroundColour(target[0], target[1], wxColour(255, 0, 0)); // red
    gridPtr->ForceRefresh();

    /*
        Take note that minTravelCost[target[0]][target[1]] will have same value as distanceTravelled[target[0]][target[1]].
        This is because the ManhattanDistance will equal to zero, and hence travelCost will be equal to distanceTravalled.
        However, we will return distanceTravelled to avoid confusion.
    */
    return {numOfCellsVisited, numOfCellCheckingOccurrence, distanceTravelled[target[0]][target[1]], prev};
}

int getManhattanDistance(std::array<int, 2> currentCell, std::array<int, 2> targetCell)
{
    return abs(targetCell[1] - currentCell[1]) + abs(targetCell[0] - currentCell[0]);
}