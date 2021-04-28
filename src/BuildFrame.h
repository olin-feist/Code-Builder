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

using namespace std;

class BuildFrame : public wxFrame{
    public:
        BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
        wxPanel* panel_top;
        wxPanel* panel_bottom;
        wxGridSizer *panelsizer;
        wxBoxSizer *panelsizerbot;
        wxButton *createbtn;
        wxTextCtrl *filename;
        wxDirPickerCtrl *filePickerCtrl;

    private:
        void OnFactory(wxCommandEvent &event);
        void OnObserver(wxCommandEvent &event);

        void choiceSelected(wxCommandEvent& event);
        void amountSelected(wxCommandEvent& event);
        bool validateinput(vector<string> v);

        vector<wxControl*> attributes;

        wxDECLARE_EVENT_TABLE();
};

//enum for event id's
enum{
    ID_Factory = 1,
    ID_Observer = wxID_HIGHEST + 1,
    choiceevent = wxID_HIGHEST + 1,
    amountsec = wxID_HIGHEST + 1
};

