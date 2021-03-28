
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

int main(){
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
    }

    return 0;
}

class MyApp : public wxApp{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame{
    public:
        MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    private:
        void OnHello(wxCommandEvent &event);
        void OnExit(wxCommandEvent &event);
        void OnAbout(wxCommandEvent &event);
        wxDECLARE_EVENT_TABLE();
};

enum{
    ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello, MyFrame::OnHello)
        EVT_MENU(wxID_EXIT, MyFrame::OnExit)
            EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
                wxEND_EVENT_TABLE()
                    wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
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
}

void MyFrame::OnExit(wxCommandEvent &event){
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event){
    wxMessageBox("This is a wxWidgets' Hello world sample",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event){
    wxLogMessage("Hello world from wxWidgets!");
}

