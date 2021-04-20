
#include <iostream>
#include <vector>
#include "cppbuilder.h"
#include <fstream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

using namespace std;

void writeFile(vector<string> v){
    ofstream file("newCpp.cpp");

    for(string l:v){
        file<<l<<endl;
    }
    file.close();
}


class MyApp : public wxApp{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame{
    public:
        MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
        wxPanel* panel_top;
        

    private:
       
        void OnQuit(wxCommandEvent &event);
        void BuildMenu(wxCommandEvent &event);
        
        wxDECLARE_EVENT_TABLE();
};

class BuildFrame : public wxFrame{
    public:
        BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
        wxPanel* panel_top;
        wxBoxSizer *panelsizer;

    private:
        void OnFactory(wxCommandEvent &event);
        void OnObserver(wxCommandEvent &event);

        void choiceSelected(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};

enum{
    ID_Factory = 1,
    ID_Observer = wxID_HIGHEST + 1,
    newcpp = wxID_HIGHEST + 1,
    choiceevent =wxID_HIGHEST+1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(newcpp,  MyFrame::BuildMenu)
    EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
wxEND_EVENT_TABLE()


wxBEGIN_EVENT_TABLE(BuildFrame, wxFrame)
    EVT_BUTTON(ID_Factory, BuildFrame::OnFactory)
    EVT_BUTTON(ID_Observer,  BuildFrame::OnObserver)
    EVT_CHOICE(choiceevent,BuildFrame::choiceSelected)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);




MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_top->SetBackgroundColour(wxColor(100, 100, 200));

    wxPanel *panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_bottom->SetBackgroundColour(wxColor(100, 200, 100));

   

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10);
    sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);

    this->SetSizerAndFit(sizer);

    wxBoxSizer *panelsizer = new wxBoxSizer(wxVERTICAL);



    panel_top->SetSizerAndFit(panelsizer);
    
    wxMenuBar *menubar;
    wxMenu *file;
    wxMenuItem *quit;

    menubar = new wxMenuBar;
    file = new wxMenu;
    wxMenu* newFile = new wxMenu;

    //new file submenu
    newFile->Append(newcpp, wxT("C++"));
    newFile->Append(wxID_ANY, wxT("Java"));
    newFile->Append(wxID_ANY, wxT("Python"));
    file->AppendSubMenu(newFile, wxT("New File"));

    file->Append(wxID_ANY, wxT("&Open"));
    file->AppendSeparator();

    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    file->Append(quit);

    menubar->Append(file, wxT("&File"));
    SetMenuBar(menubar);

    SetClientSize(wxSize(1000,800));
}

BuildFrame::BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_top->SetBackgroundColour(wxColor(100, 100, 200));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10);
    

    this->SetSizerAndFit(sizer);

    panelsizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString str;
    str.Add("Factory");
    str.Add("Observer");
    wxChoice *wxCh = new wxChoice(panel_top,choiceevent, wxDefaultPosition, wxSize(100, 25),str);
    wxCh->SetMaxSize(wxSize(100, 25));
    
    
    panelsizer->Add(wxCh, 1, wxEXPAND | wxALL, 10);

    panel_top->SetSizerAndFit(panelsizer);

    SetClientSize(wxSize(400,400));
}

MyFrame *mainframe = new MyFrame("Code Builder", wxPoint(100, 100), wxSize(1100, 800));
BuildFrame* Frame;



void BuildFrame::OnFactory(wxCommandEvent &event){
    cout<<"factory"<<endl;
}

void BuildFrame::OnObserver(wxCommandEvent& event){
    cout<<"Observer"<<endl;
}

void MyFrame::OnQuit(wxCommandEvent& event){

    Close(true);
}

void BuildFrame::choiceSelected(wxCommandEvent& event){
    



    wxButton *factorybutton = new wxButton(this->panel_top, ID_Factory, _T("Factory"),wxDefaultPosition,wxSize(100, 25), 0);
    wxButton *observerbutton = new wxButton(this->panel_top, ID_Observer, _T("Observer"),wxDefaultPosition, wxSize(100, 25), 0);
    
    observerbutton->SetMaxSize(wxSize(100, 25));
    factorybutton->SetMaxSize(wxSize(100, 25));
    
    this->panelsizer->Add(factorybutton, 1, wxEXPAND | wxALL, 10);
    this->panelsizer->Add(observerbutton, 1, wxEXPAND | wxALL, 10);

    panel_top->SetSizerAndFit(panelsizer);
    
    
}

void MyFrame::BuildMenu(wxCommandEvent& event){
    Frame = new BuildFrame("C++ Builder", wxPoint(100, 100), wxSize(800, 800));
    Frame->Show();
}




bool MyApp::OnInit(){
    
    mainframe->Show(true);
    
    /*
    cppbuilder build;

    string input;
    cin>>input;
    if(input=="singleton"){
        string name;
        cout<<"Class Name: "<<endl;
        cin>>name;
        writeFile(build.singletonbuilder(name));
        
    }else if(input=="factory"){
        string headname;
        string methodname;
        //get main class name
        cout<<"Main Class Name: "<<endl;
        cin>>headname;
        //get method name
        cout<<"Method Name: "<<endl;
        cin>>methodname;
        //get classes names
        cout<<"Classes Name: "<<endl;
        string classname;
        vector<string> v;
        while(classname!="end"){
            cin>>classname;
            if(classname!="end"){
                v.push_back(classname);
            }
        }

        writeFile(build.factorybuilder(headname,methodname,v));

    }else if(input=="command"){
        string refclass;
        string invokerclass;
        vector<string> classnames;

        cout<<"Reference Class Name: "<<endl;
        cin>>refclass;

        cout<<"Invoker Class  Name: "<<endl;
        cin>>invokerclass;       
        string classname;
        while(classname!="end"){
            cout<<"Command Classes Name: "<<endl;
            
            cin>>classname;
            if(classname!="end"){
                classnames.push_back(classname);
            }
        }

         writeFile(build.commandbuilder(refclass,invokerclass,classnames));
         

    }else if(input=="observer"){
        string classname;
        cout<<"Subject Class Name"<<endl;
        cin>>classname;
        writeFile(build.observerbuilder(classname));
    }*/

    
    return true;
}



