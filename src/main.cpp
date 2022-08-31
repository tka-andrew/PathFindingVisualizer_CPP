#include "main.h"
#include "mainFrame.h"

#include <signal.h>

wxIMPLEMENT_APP(PathFindingVisualizerApp);

// Reference: https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
void interactive_signal_callback_handler(int signum) {
   std::cout << "\nCaught interactive signal: " << signum << std::endl;
   std::cout << "Terminatng program" << std::endl;
   std::exit(signum);
}

bool PathFindingVisualizerApp::OnInit()
{

    // Register interactive signal and interactive signal handler
    signal(SIGINT, interactive_signal_callback_handler);

    MainFrame *frame = new MainFrame("Path Finding Visualizer App", wxPoint(50, 50), wxSize(1440, 930));
    frame->Show(true);
    return true;
}
