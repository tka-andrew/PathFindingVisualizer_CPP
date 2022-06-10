#include "pathFindingAlgorithms.h"
#include "heuristicFunctions.h"

#include <wx/wx.h>

#include <array>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <climits>

typedef std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> MinHeap;

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> dijkstraSingleTarget(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation)
{
    wxGrid *gridPtr = mainFramePtr->m_lp->grid;

    // VARIABLLE DECLARATION
    std::vector<std::vector<int>> minTravelCost(gridRow, std::vector<int>(gridCol, INT_MAX));
    std::vector<std::vector<std::array<int, 2>>> prev(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<int>> visited(gridRow, std::vector<int>(gridCol, false));

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int numOfCellsVisited = 0;
    int numOfCellCheckingOccurrence = 0;
    bool foundTarget = false; // not used as it conflicts with Dijkstra's Algorithm

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

        if (showAnimation)
        {
            // INSPIRED BY: https://github.com/ArturMarekNowak/Pathfinding-Visualization/blob/master/SourceFiles/cMain.cpp
            mainFramePtr->Update();
            mainFramePtr->Refresh(false);
        }
    }

    mainFramePtr->m_rp->repaintPoints();
    gridPtr->ForceRefresh();

    return {numOfCellsVisited, numOfCellCheckingOccurrence, minTravelCost[target[0]][target[1]], prev};
}

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> aStarSearch(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation)
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
    minHeap.push({getManhattanDistance(source, target), source[0], source[1]}); // {travelCost, r, c}

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

        if (showAnimation)
        {
            // INSPIRED BY: https://github.com/ArturMarekNowak/Pathfinding-Visualization/blob/master/SourceFiles/cMain.cpp
            mainFramePtr->Update();
            mainFramePtr->Refresh(false);
        }
    }

    mainFramePtr->m_rp->repaintPoints();
    gridPtr->ForceRefresh();

    /*
        Take note that minTravelCost[target[0]][target[1]] will have same value as distanceTravelled[target[0]][target[1]].
        This is because the ManhattanDistance will equal to zero, and hence travelCost will be equal to distanceTravalled.
        However, we will return distanceTravelled to avoid confusion.
    */
    return {numOfCellsVisited, numOfCellCheckingOccurrence, distanceTravelled[target[0]][target[1]], prev};
}

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> greedyBestFirstSearch(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation)
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
            int newTravelCost = getManhattanDistance({newR, newC}, target); // dont consider distance travelled
            
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

        if (showAnimation)
        {
            // INSPIRED BY: https://github.com/ArturMarekNowak/Pathfinding-Visualization/blob/master/SourceFiles/cMain.cpp
            mainFramePtr->Update();
            mainFramePtr->Refresh(false);
        }
    }

    mainFramePtr->m_rp->repaintPoints();
    gridPtr->ForceRefresh();

    return {numOfCellsVisited, numOfCellCheckingOccurrence, distanceTravelled[target[0]][target[1]], prev};
}

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> bfs(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation)
{
    wxGrid *gridPtr = mainFramePtr->m_lp->grid;

    // VARIABLLE DECLARATION
    std::vector<std::vector<std::array<int, 2>>> prev(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<int>> visited(gridRow, std::vector<int>(gridCol, false));

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int numOfCellsVisited = 0;
    int numOfCellCheckingOccurrence = 0;

    int travelCost = 0;
    bool foundTarget = false;

    std::queue<std::pair<int, int>> q;
    q.push({source[0], source[1]});


    while (!q.empty())
    {
        int n = q.size();

        for (int i=0; i<n; i++)
        {
            auto currentNode = q.front();
            int curR = currentNode.first;
            int curC = currentNode.second;
            q.pop();

            if (visited[curR][curC])
            {
                continue;
            }

            visited[curR][curC] = true;
            numOfCellsVisited++;

            if (curR == target[0] && curC == target[1])
            {
                foundTarget = true;
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

                prev[newR][newC] = {curR, curC};
                q.push({newR, newC});
            }

            if (showAnimation)
            {
                // INSPIRED BY: https://github.com/ArturMarekNowak/Pathfinding-Visualization/blob/master/SourceFiles/cMain.cpp
                mainFramePtr->Update();
                mainFramePtr->Refresh(false);
            }
        }

        // break before adding travelCost
        // because the cell checking step has already considered the travelCost
        if (foundTarget) break;

        travelCost++;

    }

    if (!foundTarget) travelCost = INT_MAX; 

    mainFramePtr->m_rp->repaintPoints();
    gridPtr->ForceRefresh();

    return {numOfCellsVisited, numOfCellCheckingOccurrence, travelCost, prev};
}

// REFERENCE: https://www.geeksforgeeks.org/unordered-set-of-pairs-in-c-with-examples/
// Hash function 
struct hashFunction
{
  size_t operator()(const std::pair<int , 
                    int> &x) const
  {
    return x.first ^ x.second;
  }
};

std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> bidirectionalBFS(std::array<int, 2> source, std::array<int, 2> target, int gridRow, int gridCol, MainFrame *mainFramePtr, bool showAnimation)
{
    wxGrid *gridPtr = mainFramePtr->m_lp->grid;

    // VARIABLLE DECLARATION
    std::vector<std::vector<std::array<int, 2>>> prev_s(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<std::array<int, 2>>> prev_t(gridRow, std::vector<std::array<int, 2>>(gridCol, {-1, -1}));
    std::vector<std::vector<int>> visited(gridRow, std::vector<int>(gridCol, false));

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int numOfCellsVisited = 0;
    int numOfCellCheckingOccurrence = 0;

    int travelCost = 0;
    bool foundTarget = false;

    // use set insead of queue, for faster identifying existence of an element
    std::unordered_set<std::pair<int, int>, hashFunction> s1;
    std::unordered_set<std::pair<int, int>, hashFunction> s2;
    s1.insert({source[0], source[1]});
    s2.insert({target[0], target[1]});

    std::pair<int, int> intersectionPoint;

    bool isProcessingSourceEnd = true;

    while (!s1.empty() && !s2.empty())
    {
        // Minor Enhancement
        // swap s1 and s2 when s1 has larger size
        // so that BFS is perform on set with smaller size first
        // as smaller size of set will result in smaller expansion
        if (s1.size() > s2.size()) {
            std::unordered_set<std::pair<int, int>, hashFunction> tempForSwap = s1;
            s1=s2;
            s2=tempForSwap;
            isProcessingSourceEnd = !isProcessingSourceEnd;
        }
        

        int n = s1.size();
        std::unordered_set<std::pair<int, int>, hashFunction> temp;
        
        for (const auto& blueCell:s1)
        {
            auto currentNode = blueCell;
            int curR = currentNode.first;
            int curC = currentNode.second;

            if (visited[curR][curC])
            {
                continue;
            }

            visited[curR][curC] = true;
            numOfCellsVisited++;

            gridPtr->SetCellBackgroundColour(curR, curC, wxColour(0, 0, 125)); // dark blue

            if (s2.find(blueCell) != s2.end()) { // means both end already met
                intersectionPoint = blueCell;
                foundTarget = true;
                break;
            }

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

                if (isProcessingSourceEnd)
                    prev_s[newR][newC] = {curR, curC};
                else
                    prev_t[newR][newC] = {curR, curC};
                temp.insert({newR, newC});
            }

            if (showAnimation)
            {
                // INSPIRED BY: https://github.com/ArturMarekNowak/Pathfinding-Visualization/blob/master/SourceFiles/cMain.cpp
                mainFramePtr->Update();
                mainFramePtr->Refresh(false);
            }
        }

        // break before adding travelCost
        // because the cell checking step has already considered the travelCost
        if (foundTarget) 
        {
            // /* PREV_S
            //                            intersection                target
            //   source                       point
            //     @   <-   @   <-    @   <-    @       @       @       @ 
            //                                  q       r              
            // */
            // /* PREV_T
            //                            intersection                target
            //   source                       point
            //     @        @         @         @  ->   @  ->   @   ->  @
            //                                  q       r              
            // */
            int qRow = intersectionPoint.first;
            int qCol = intersectionPoint.second;
            int rRow = prev_t[qRow][qCol][0];
            int rCol = prev_t[qRow][qCol][1];
            while (rRow != -1 && rCol != -1)
            {
                prev_s[rRow][rCol] = {qRow, qCol};
                qRow = rRow;
                qCol = rCol;
                int tempRRow = rRow;
                int tempRCol = rCol;
                rRow = prev_t[tempRRow][tempRCol][0];
                rCol = prev_t[tempRRow][tempRCol][1];
            }
            break;
        }

        // switch s1 and s2 to take turn perform BFS from both ends
        s1=s2;
        s2=temp;
        travelCost++;
        isProcessingSourceEnd = !isProcessingSourceEnd;
    }

    if (!foundTarget) travelCost = INT_MAX;

    mainFramePtr->m_rp->repaintPoints();
    gridPtr->ForceRefresh();

    return {numOfCellsVisited, numOfCellCheckingOccurrence, travelCost, prev_s};
}
