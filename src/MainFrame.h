#include <iostream>
#include <vector>
#include <fstream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filepicker.h>
#include <wx/combo.h>
#include <wx/listctrl.h>
#include <wx/odcombo.h>
#include <wx/wx.h>
#include <wx/dirctrl.h>

class MainFrame : public wxFrame{
    public:
        MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
        

    private:
        wxPanel* panel_left;
        wxPanel* panel_right;
        wxTextCtrl* textedit=new wxTextCtrl();
        wxTreeCtrl* filetree=new wxTreeCtrl();
        
        void OnQuit(wxCommandEvent &event);
        void BuildMenu(wxCommandEvent &event);
        void OpenFile(wxCommandEvent &event);
        
        wxDECLARE_EVENT_TABLE();
};


