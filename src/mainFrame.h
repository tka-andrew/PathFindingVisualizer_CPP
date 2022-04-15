#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "panels.h"  

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/panel.h>

#include<array>

class wxGrid;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    LeftPanel *m_lp;
    RightPanel *m_rp;
    wxPanel *m_parent;
    std::array<int, 2> startingPoint = {-1, -1};
    std::array<int, 2> destinationPoint = {-1, -1};
    bool startingPointDefined = false;
    bool destinationPointDefined = false;

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1
};


#endif