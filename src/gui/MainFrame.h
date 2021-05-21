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
        wxString filename;
        
        void OnQuit(wxCommandEvent &event);
        void BuildMenuJava(wxCommandEvent &event);
        void BuildMenuCpp(wxCommandEvent &event);
        void BuildMenuPython(wxCommandEvent& event);
        void OpenFile(wxCommandEvent &event);
        void OpenConsole(wxCommandEvent& event);
        void AddGetters(wxCommandEvent& event);
        void AddSetters(wxCommandEvent& event);
        void ReparInfo(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};


