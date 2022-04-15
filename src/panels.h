#ifndef PANELS_H
#define PANELS_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/grid.h>


class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
    wxGrid *grid;
    wxPanel *m_parent;
    int gridRow = 40;
    int gridCol = 60;
};

class RightPanel : public wxPanel
{
public:

    RightPanel(wxPanel *parent);

    void OnSetWall(wxCommandEvent & event);
    void OnUnsetWall(wxCommandEvent & event);
    void OnSetStartingPoint(wxCommandEvent & event);
    void OnSetDestinationPoint(wxCommandEvent & event);
    void OnStartSimulation(wxCommandEvent & event);

    wxButton *m_setWall;
    wxButton *m_unsetWall;
    wxButton *m_setStartingPoint;
    wxButton *m_setDestinationPoint;
    wxButton *m_startSimulation;
    wxPanel *m_parent;
};

const int ID_SET_WALL = 101;
const int ID_UNSET_WALL = 102;
const int ID_SET_STARTING_POINT = 103;
const int ID_SET_DESTINATION_POINT = 104;
const int ID_START_SIMULATION = 105;

#endif // PANELS_H