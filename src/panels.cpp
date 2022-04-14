#include <wx/stattext.h>
#include "mainFrame.h"
#include "panels.h"

RightPanel::RightPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_setStartingPoint = new wxButton(this, ID_SET_STARTING_POINT, wxT("Set Starting Point"),
                                      wxPoint(10, 10));
    m_setDestinationPoint = new wxButton(this, ID_SET_DESTINATION_POINT, wxT("Set Destination Point"),
                                         wxPoint(10, 60));
    m_startSimulation = new wxButton(this, ID_START_SIMULATION, wxT("Start Simulation"),
                                     wxPoint(10, 110));
    Connect(ID_SET_STARTING_POINT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnSetStartingPoint));
    Connect(ID_SET_DESTINATION_POINT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnSetDestinationPoint));
    Connect(ID_START_SIMULATION, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(RightPanel::OnStartSimulation));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // Second button takes the full space
    sizer->Add(m_setStartingPoint, 0, wxEXPAND, 0);
    sizer->Add(m_setDestinationPoint, 0, wxEXPAND, 0);
    sizer->Add(m_startSimulation, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void RightPanel::OnSetStartingPoint(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage("OnSetStartingPoint");
}

void RightPanel::OnSetDestinationPoint(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage("OnSetDestinationPoint");
}

void RightPanel::OnStartSimulation(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage("OnStartSimulation");
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
    
    grid->CreateGrid(40, 60);

    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();

    wxBoxSizer *hbox = new wxBoxSizer(wxVERTICAL);
    hbox->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    // hbox->Add(grid, 1, wxEXPAND | wxALL, 20);
    this->SetSizer(hbox);
}