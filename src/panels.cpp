#include "mainFrame.h"
#include "panels.h"
#include "pathFindingAlgorithms.h"

#include <queue>
#include <vector>
#include <climits>
#include <math.h>
#include <thread>
#include <future>


RightPanel::RightPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_setWall = new wxButton(this, ID_SET_WALL, wxT("Set Wall"),
                             wxPoint(10, 10));
    m_unsetWall = new wxButton(this, ID_UNSET_WALL, wxT("Unset Wall"),
                               wxPoint(10, 10));
    m_setStartingPoint = new wxButton(this, ID_SET_STARTING_POINT, wxT("Set Starting Point"),
                                      wxPoint(10, 60));
    m_setDestinationPoint = new wxButton(this, ID_SET_DESTINATION_POINT, wxT("Set Destination Point"),
                                         wxPoint(10, 110));
    m_startSimulation = new wxButton(this, ID_START_SIMULATION, wxT("Start Simulation"),
                                     wxPoint(10, 160));
    m_resetGrid = new wxButton(this, ID_RESET_GRID, wxT("Reset Grid"),
                                     wxPoint(10, 210));
    Connect(ID_SET_WALL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnSetWall));
    Connect(ID_UNSET_WALL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnUnsetWall));
    Connect(ID_SET_STARTING_POINT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnSetStartingPoint));
    Connect(ID_SET_DESTINATION_POINT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnSetDestinationPoint));
    Connect(ID_START_SIMULATION, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnStartSimulation));
    Connect(ID_RESET_GRID, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnResetGrid));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // Second button takes the full space
    sizer->Add(m_setWall, 0, wxEXPAND, 0);
    sizer->Add(m_unsetWall, 0, wxEXPAND, 0);
    sizer->Add(m_setStartingPoint, 0, wxEXPAND, 0);
    sizer->Add(m_setDestinationPoint, 0, wxEXPAND, 0);
    sizer->Add(m_startSimulation, 0, wxEXPAND, 0);
    sizer->Add(m_resetGrid, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void RightPanel::OnSetWall(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=34690
    // REFERENCE: https://docs.wxwidgets.org/trunk/classwx_grid.html#affcd2c7ebc133bd2bb7ed4147a6baff1
    // According to the documentation, GetSelectedCells() will return empty array
    // Hence, we need to use GetSelectionBlockTopLeft() and GetSelectionBlockBottomRight()
    wxGridCellCoordsArray topLeftCells = mainFrame->m_lp->grid->GetSelectionBlockTopLeft();
    wxGridCellCoordsArray bottomRightCells = mainFrame->m_lp->grid->GetSelectionBlockBottomRight();
    for (int i = 0; i < topLeftCells.Count(); i++)
    {

        int rowTopLeft = topLeftCells[i].GetRow();
        int colTopLeft = topLeftCells[i].GetCol();
        int rowBottomRight = bottomRightCells[i].GetRow();
        int colBottomRight = bottomRightCells[i].GetCol();
        for (int j = rowTopLeft; j <= rowBottomRight; j++)
        {
            for (int k = colTopLeft; k <= colBottomRight; k++)
            {
                mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
            }
        }
    }
    mainFrame->m_lp->grid->ClearSelection();
}

void RightPanel::OnUnsetWall(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=34690
    // REFERENCE: https://docs.wxwidgets.org/trunk/classwx_grid.html#affcd2c7ebc133bd2bb7ed4147a6baff1
    // According to the documentation, GetSelectedCells() will return empty array
    // Hence, we need to use GetSelectionBlockTopLeft() and GetSelectionBlockBottomRight()
    wxGridCellCoordsArray topLeftCells = mainFrame->m_lp->grid->GetSelectionBlockTopLeft();
    wxGridCellCoordsArray bottomRightCells = mainFrame->m_lp->grid->GetSelectionBlockBottomRight();
    for (int i = 0; i < topLeftCells.Count(); i++)
    {

        int rowTopLeft = topLeftCells[i].GetRow();
        int colTopLeft = topLeftCells[i].GetCol();
        int rowBottomRight = bottomRightCells[i].GetRow();
        int colBottomRight = bottomRightCells[i].GetCol();
        for (int j = rowTopLeft; j <= rowBottomRight; j++)
        {
            for (int k = colTopLeft; k <= colBottomRight; k++)
            {
                mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(255, 255, 255)); // white
            }
        }
    }
    mainFrame->m_lp->grid->ClearSelection();
}

void RightPanel::OnSetStartingPoint(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    if (mainFrame->startingPointDefined)
    {
        int previousRow = mainFrame->startingPoint[0];
        int previousCol = mainFrame->startingPoint[1];
        mainFrame->m_lp->grid->SetCellBackgroundColour(previousRow, previousCol, wxColour(255, 255, 255)); // white
    }

    wxGridCellCoordsArray topLeftCells = mainFrame->m_lp->grid->GetSelectionBlockTopLeft();

    if (topLeftCells.Count() > 0)
    {
        // only use the first cell even if multiple cells selected
        int row = topLeftCells[0].GetRow();
        int col = topLeftCells[0].GetCol();

        mainFrame->m_lp->grid->SetCellBackgroundColour(row, col, wxColour(0, 255, 0)); // green
        mainFrame->m_lp->grid->ClearSelection();

        // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=29984
        // To repaint the grid immediately
        mainFrame->m_lp->grid->ForceRefresh();

        // update memory
        mainFrame->startingPointDefined = true;
        mainFrame->startingPoint[0] = row;
        mainFrame->startingPoint[1] = col;
    }
}

void RightPanel::OnSetDestinationPoint(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    if (mainFrame->destinationPointDefined)
    {
        int previousRow = mainFrame->destinationPoint[0];
        int previousCol = mainFrame->destinationPoint[1];
        mainFrame->m_lp->grid->SetCellBackgroundColour(previousRow, previousCol, wxColour(255, 255, 255)); // white
    }

    wxGridCellCoordsArray topLeftCells = mainFrame->m_lp->grid->GetSelectionBlockTopLeft();

    if (topLeftCells.Count() > 0)
    {
        // only use the first cell even if multiple cells selected
        int row = topLeftCells[0].GetRow();
        int col = topLeftCells[0].GetCol();

        mainFrame->m_lp->grid->SetCellBackgroundColour(row, col, wxColour(255, 0, 0)); // red
        mainFrame->m_lp->grid->ClearSelection();

        // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=29984
        // To repaint the grid immediately
        mainFrame->m_lp->grid->ForceRefresh();

        // update memory
        mainFrame->destinationPointDefined = true;
        mainFrame->destinationPoint[0] = row;
        mainFrame->destinationPoint[1] = col;
    }
}

void RightPanel::OnStartSimulation(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    if (!mainFrame->startingPointDefined || !mainFrame->destinationPointDefined)
    {
        wxLogMessage("Please define your starting point and destination point first.");
        return;
    }

    int startingPoint[2]{mainFrame->startingPoint[0], mainFrame->startingPoint[1]};
    int destinationPoint[2]{mainFrame->destinationPoint[0], mainFrame->destinationPoint[1]};
    typedef std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> MinHeap;

    std::vector<std::vector<int>> minTravelCost(mainFrame->m_lp->gridRow, std::vector<int>(mainFrame->m_lp->gridCol, INT_MAX));
    minTravelCost[startingPoint[0]][startingPoint[1]] = 0;

    int row = mainFrame->m_lp->gridRow;
    int col = mainFrame->m_lp->gridCol;
    int targetR = destinationPoint[0];
    int targetC = destinationPoint[1];
    
    // std::thread ss(dijkstraSingleTarget,startingPoint, destinationPoint, row, col, mainFrame);
    // ss.join();

    // REFERENCE: https://stackoverflow.com/questions/7686939/c-simple-return-value-from-stdthread
    // auto future = std::async(dijkstraSingleTarget,startingPoint, destinationPoint, row, col, mainFrame);
    // auto resultPair = future.get();

    auto [pointExplored, shortestDistance, prev] = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, mainFrame);
    std::array<int, 2> pathTrackCell {prev[targetR][targetC]};
    while(pathTrackCell[0] != -1 && pathTrackCell[1] != -1 )
    {
        int row = pathTrackCell[0];
        int col = pathTrackCell[1];
        mainFrame->m_lp->grid->SetCellBackgroundColour(row, col, wxColour(100, 100, 100));
        pathTrackCell[0] = prev[row][col][0];
        pathTrackCell[1] = prev[row][col][1];
    }

    // paint the starting point back to green
    mainFrame->m_lp->grid->SetCellBackgroundColour(startingPoint[0], startingPoint[1], wxColour(0, 255, 0)); // green
    mainFrame->m_lp->grid->ForceRefresh();

    wxLogMessage("Number of points explored: %d\nMinimum distance %d", pointExplored, shortestDistance);
}

/**
 * @brief Reset cells except startingPoint, destinationPoint and walls
 */
void RightPanel::OnResetGrid(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    int startingPoint[2] = {mainFrame->startingPoint[0], mainFrame->startingPoint[1]};
    int destinationPoint[2] = {mainFrame->destinationPoint[0], mainFrame->destinationPoint[1]};
    for (int i = 0; i<mainFrame->m_lp->gridRow; i++)
    {
        for (int j = 0; j<mainFrame->m_lp->gridCol; j++)
        {
            if (i == startingPoint[0] && j == startingPoint[1])
            {
                continue;
            }
            if (i == destinationPoint[0] && j == destinationPoint[1])
            {
                continue;
            }
            if (mainFrame->m_lp->grid->GetCellBackgroundColour(i, j) != wxColor(0, 0, 0))
            {
                mainFrame->m_lp->grid->SetCellBackgroundColour(i, j, wxColour(255, 255, 255));
            }
        }
    }
    mainFrame->m_lp->grid->ForceRefresh();
}

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(200, 200), wxBORDER_SUNKEN)
{

    // Create a wxGrid object
    grid = new wxGrid(this,
                      -1,
                      wxPoint(0, 0),
                      wxSize(200, 200));

    // This 2 lines must be executed before CreateGrid()
    grid->SetDefaultColSize(20);
    grid->SetDefaultRowSize(20);

    grid->CreateGrid(this->gridRow, this->gridCol);

    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();

    wxBoxSizer *hbox = new wxBoxSizer(wxVERTICAL);
    hbox->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    // hbox->Add(grid, 1, wxEXPAND | wxALL, 20);
    this->SetSizer(hbox);
}