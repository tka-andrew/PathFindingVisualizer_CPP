#include "main.h"
#include "mainFrame.h"

wxIMPLEMENT_APP(PathFindingVisualizerApp);

bool PathFindingVisualizerApp::OnInit()
{
    MainFrame *frame = new MainFrame("Path Finding Visualizer App", wxPoint(50, 50), wxSize(1440, 930));
    frame->Show(true);
    return true;
}
