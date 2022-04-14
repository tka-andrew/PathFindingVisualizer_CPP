#include "mainFrame.h"

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
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
    SetStatusText("Welcome to wxWidgets!");

    // Create a wxGrid object
    grid = new wxGrid( this,
                        -1,
                        wxPoint( 0, 0 ),
                        wxSize( 200, 200 ) );
    // Then we call CreateGrid to set the dimensions of the grid
    // (100 rows and 100 columns in this example)
    grid->CreateGrid(40, 80);
    // We can set the sizes of individual rows and columns
    // in pixels
    // grid->SetRowSize( 0, 50 );
    // grid->SetColSize( 0, 50 );
    // And set grid cell contents as strings
    // grid->SetCellValue( 0, 0, "wxGrid is good" );
    // // We can specify that some cells are read->only
    // grid->SetCellValue( 0, 3, "This is read->only" );
    // grid->SetReadOnly( 0, 3 );
    // Colours can be specified for grid cell contents
    // grid->SetCellValue(3, 3, "green on grey");
    // grid->SetCellTextColour(3, 3, *wxGREEN);
    // grid->SetReadOnly( 3, 3 );
    // grid->SetCellBackgroundColour(3, 3, *wxBLACK);
    // We can specify the some cells will store numeric
    // values rather than strings. Here we set grid column 5
    // to hold floating point values displayed with width of 6
    // and precision of 2
    // grid->SetColFormatFloat(5, 6, 2);
    // grid->SetCellValue(0, 6, "3.1415");

    grid->SetDefaultColSize(20);
    grid->SetDefaultRowSize(20);
    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();

    Centre();

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