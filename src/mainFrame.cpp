#include "mainFrame.h"

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
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
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
void MainFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Just a dummy Hello World!");
}