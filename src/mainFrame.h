#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "panels.h"  

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/panel.h>

class wxGrid;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    LeftPanel *m_lp;
    RightPanel *m_rp;
    wxPanel *m_parent;

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