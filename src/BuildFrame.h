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

class BuildFrame:public wxFrame{

    protected:
        wxPanel* panel_top;
        wxPanel* panel_bottom;
        wxPanel* panel_right;
        wxPanel* panel_left;
        wxButton *createbtn;
        wxTextCtrl *filename;
        wxDirPickerCtrl *filePickerCtrl;
        vector<wxControl*> attributes;

        BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size):wxFrame(NULL, wxID_ANY, title, pos, size){}
        
        void OnFactory(wxCommandEvent &event);
        void OnObserver(wxCommandEvent &event);
        void OnCommand(wxCommandEvent &event);
        void OnSingleton(wxCommandEvent &event);

        void choiceSelected(wxCommandEvent& event);
        void amountSelected(wxCommandEvent& event);
        bool validateinput(vector<string> v);

        

        
};

class buildframec : public BuildFrame{

    public:
        buildframec(const wxString &title, const wxPoint &pos, const wxSize &size);

    private:
        void OnFactory(wxCommandEvent &event);
        void OnObserver(wxCommandEvent &event);
        void OnCommand(wxCommandEvent &event);
        void OnSingleton(wxCommandEvent &event);

        void choiceSelected(wxCommandEvent& event);
        void amountSelected(wxCommandEvent& event);
        bool validateinput(vector<string> v);
    

    wxDECLARE_EVENT_TABLE();
};

class buildframeJava : public BuildFrame{

    public:
        buildframeJava(const wxString &title, const wxPoint &pos, const wxSize &size);

    private:
        void OnFactory(wxCommandEvent &event);
        void OnObserver(wxCommandEvent &event);
        void OnCommand(wxCommandEvent &event);
        void OnSingleton(wxCommandEvent &event);

        void choiceSelected(wxCommandEvent& event);
        void amountSelected(wxCommandEvent& event);
        bool validateinput(vector<string> v);

    wxDECLARE_EVENT_TABLE();
};

class buildframePy : public BuildFrame{

    public:
        buildframePy(const wxString &title, const wxPoint &pos, const wxSize &size);

    private:
        void OnFactory(wxCommandEvent &event);
        void OnObserver(wxCommandEvent &event);
        void OnCommand(wxCommandEvent &event);
        void OnSingleton(wxCommandEvent &event);

        void choiceSelected(wxCommandEvent& event);
        void amountSelected(wxCommandEvent& event);
        bool validateinput(vector<string> v);

    wxDECLARE_EVENT_TABLE();
};


