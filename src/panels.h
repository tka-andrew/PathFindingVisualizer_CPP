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

};

class RightPanel : public wxPanel
{
public:

    RightPanel(wxPanel *parent);

    void OnSetStartingPoint(wxCommandEvent & event);
    void OnSetDestinationPoint(wxCommandEvent & event);
    void OnStartSimulation(wxCommandEvent & event);

    wxButton *m_setStartingPoint;
    wxButton *m_setDestinationPoint;
    wxButton *m_startSimulation;
    wxPanel *m_parent;
};

const int ID_SET_STARTING_POINT = 101;
const int ID_SET_DESTINATION_POINT = 102;
const int ID_START_SIMULATION = 103;

#endif // PANELS_H