#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_MENU(ID_USAGEGUIDE, MainFrame::OnUsageGuide)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    m_parent = new wxPanel(this, wxID_ANY);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    m_lp = new LeftPanel(m_parent);
    m_rp = new RightPanel(m_parent);

    hbox->Add(m_lp, 1, wxEXPAND, 5);
    hbox->Add(m_rp, 0, wxSHAPED, 5);

    m_parent->SetSizer(hbox);

    this->Centre();

    wxMenu *menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuHelp->Append(ID_USAGEGUIDE, "&Usage Guide...\tCtrl-H",
                     "Usage Guide");
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Path Finding Visualizer - by Tan Kui An Andrew 2022");

}

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("The main purpose of this app is to visualize the path finding algorithm written in CPP. \
    \nThis app is developed using wxWdigets. \
    \nTake note that this project is being tested on Ubuntu 20.04 environment only.",
                 "About this app", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnUsageGuide(wxCommandEvent &event)
{
    wxMessageBox("1. Setting a starting point: highlight a cell and click at the 'Set Starting Point' button \
    \n2. Setting a destination point: highlight a cell and click at the 'Set Destination Point' button \
    \n3. Setting obstacles: highlight the area that you want to set as obstacles, then click the 'Set Wall' button  \
    \n4. Removing obstacles: highlight the obstacles that you want to remove, then click the 'Unset Wall' button \
    \n5. Selecting algorithm: select either 'Dijkstra' or 'A* Search' from the dropdown \
    \n6. Starting simulation: click at the 'Start Simulation' button",
                 "Usage Guide", wxOK | wxICON_INFORMATION);
}
