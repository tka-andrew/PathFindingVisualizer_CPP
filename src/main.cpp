#include "main.h"
#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Hello, MainFrame::OnHello)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(PathFindingVisualizerApp);

bool PathFindingVisualizerApp::OnInit()
{
    MainFrame *frame = new MainFrame("Path Finding Visualizer App", wxPoint(50, 50), wxSize(1420, 930));
    frame->Show(true);
    return true;
}
