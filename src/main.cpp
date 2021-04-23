
#include <iostream>
#include <vector>
#include "cppbuilder.h"
#include <fstream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filepicker.h>

using namespace std;

void writeFile(vector<string> v, string path, string filename){
    cout<<path<<endl;
    ofstream file(path+"\\"+filename+".cpp");

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
        wxPanel* panel_bottom;
        wxBoxSizer *panelsizer;
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
    newcpp = wxID_HIGHEST + 1,
    choiceevent = wxID_HIGHEST+1,
    amountsec = 5
};

//event table for MyFrame||mainframe
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(newcpp,  MyFrame::BuildMenu)
    EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
wxEND_EVENT_TABLE()

//event table for buildframe
wxBEGIN_EVENT_TABLE(BuildFrame, wxFrame)
    EVT_BUTTON(ID_Factory, BuildFrame::OnFactory)
    EVT_BUTTON(ID_Observer,  BuildFrame::OnObserver)
    EVT_CHOICE(choiceevent,BuildFrame::choiceSelected)
    EVT_CHOICE(amountsec,BuildFrame::amountSelected)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);



//constructor for myframe
MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(380, 500));
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

    
}

//constructor for buildframe
BuildFrame::BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_top->SetBackgroundColour(wxColor(30, 30, 30));
    
    this->SetBackgroundColour(wxColor(51,51,51));

    panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 30));
    panel_bottom->SetMaxSize(wxSize(200, 50));
    panel_bottom->SetBackgroundColour(wxColor(30, 30, 30));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10);
    sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);
    

    this->SetSizerAndFit(sizer);

    panelsizer = new wxBoxSizer(wxVERTICAL);
    panelsizerbot = new wxBoxSizer(wxVERTICAL);

    wxArrayString str;
    str.Add("Factory");
    str.Add("Observer");
    wxChoice *wxCh = new wxChoice(panel_top,choiceevent, wxDefaultPosition, wxSize(100, 25),str,wxNO_BORDER);
    wxCh->SetWindowStyle(wxSIMPLE_BORDER );
    wxCh->SetMaxSize(wxSize(100, 25));
    wxCh->SetBackgroundColour(wxColor(51,51,51));
    wxCh->SetForegroundColour(wxColor(195,195,195));
    ((wxControl*) wxCh)->SetWindowStyle(wxSIMPLE_BORDER);
    
    filename = new wxTextCtrl(panel_top, wxID_ANY, wxT("filenname"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
    filename->SetMargins(wxPoint(1,10));
    filename->SetBackgroundColour(wxColor(51,51,51));
    filename->SetForegroundColour(wxColor(195,195,195));

    filePickerCtrl = new wxDirPickerCtrl(panel_top, wxID_ANY,wxEmptyString,wxDirSelectorPromptStr,wxDefaultPosition, wxSize(100, 25),wxDIRP_USE_TEXTCTRL|wxDIRP_SMALL);
    wxTextCtrl *dirtext=filePickerCtrl->GetTextCtrl();
    dirtext->SetBackgroundColour(wxColor(51,51,51));
    dirtext->SetForegroundColour(wxColor(195,195,195));
    dirtext->SetWindowStyleFlag(wxSIMPLE_BORDER);
    wxButton *btn = (wxButton*) filePickerCtrl->GetPickerCtrl();
    btn->SetBackgroundColour(wxColor(51,51,51));
    btn->SetForegroundColour(wxColor(195,195,195));
    btn->SetWindowStyleFlag(wxSIMPLE_BORDER);

    filename->SetMaxSize(wxSize(100, 25));
    filePickerCtrl->SetMaxSize(wxSize(250, 25));
    
    panelsizer->Add(wxCh, 1, wxEXPAND | wxALL, 10);
    panelsizer->Add(filename, 1, wxEXPAND | wxALL, 10);
    panelsizer->Add(filePickerCtrl, 1, wxEXPAND | wxALL, 10);

    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    

    

}

MyFrame *mainframe = new MyFrame("Code Builder", wxPoint(100, 100), wxSize(800, 800));
BuildFrame* Frame;


//check is there is user input if not send error
bool BuildFrame::validateinput(vector<string> v){
    for(string s: v){
        cout<<s<<endl;
        if(s.length()==0||s.empty()){
            wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Input"), wxT("Error"), wxOK | wxICON_ERROR);
            dial->ShowModal();
            return false;
        }
    }
    return true;
}

//creates text box based on the number of elements required
void BuildFrame::amountSelected(wxCommandEvent &event){
    cout<<attributes.size()<<endl;
    if(attributes.size()>3){
        for(int i=3;i<attributes.size();i++){
            cout<<i<<endl;
            attributes[i]->Destroy();
        }
        attributes.erase(attributes.begin()+3,attributes.end());
    }
    cout<<attributes.size()<<endl;

    for(int i=0;i<=event.GetInt();i++){
        
        wxTextCtrl *temp = new wxTextCtrl(this->panel_top, wxID_ANY, _(""), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        temp->SetMaxSize(wxSize(100, 25));
        temp->SetBackgroundColour(wxColor(51,51,51));
        temp->SetForegroundColour(wxColor(195,195,195));
        this->panelsizer->Add(temp, 1, wxEXPAND | wxALL, 10);
        attributes.push_back(temp);
    }
    


    this->panel_top->SetSizerAndFit(panelsizer);
    this->Layout();
    panel_top->Layout();
}

//create factory c++ on call
void BuildFrame::OnFactory(wxCommandEvent &event){
    
    cppbuilder build;
    string headname;
    string methodname;
    headname=((wxTextCtrl*) attributes[0])->GetValue().ToStdString();
    methodname=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();
    vector<string> test;
    test.push_back(headname);
    test.push_back(methodname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());

    

    vector<string> v;
    for(int i=3;i<attributes.size();i++){
        v.push_back(((wxTextCtrl*) attributes[i])->GetValue().ToStdString());
        cout<<v[i-3]<<endl;
    }
    
    test.insert(test.end(),v.begin(),v.end());
    if(validateinput(test)){
        writeFile(build.factorybuilder(headname,methodname,v),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
    
    

}

//create observer c++ on call
void BuildFrame::OnObserver(wxCommandEvent& event){
    cppbuilder build;
    string classname;
    classname=((wxTextCtrl*) attributes[0])->GetValue().ToStdString();

    vector<string> test;
    test.push_back(classname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());
    if(validateinput(test)){
        writeFile(build.observerbuilder(classname),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
}

//quit frame
void MyFrame::OnQuit(wxCommandEvent& event){

    Close(true);
}

//method for handling selection of different oop patterns
void BuildFrame::choiceSelected(wxCommandEvent& event){
    for(wxControl* w: attributes){
        w->Destroy();
        cout<<"test"<<endl;
    }
    attributes.clear();
    


   
    if(event.GetString()=="Factory"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(this->panel_top, wxID_ANY, wxT("MainClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        wxTextCtrl *TextCtrl2 = new wxTextCtrl(this->panel_top, wxID_ANY, wxT("MethodName"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        wxArrayString str;
        str.Add("1");
        str.Add("2");
        str.Add("3");
        str.Add("4");
        str.Add("5");
        str.Add("6");
        wxChoice *amount = new wxChoice(this->panel_top, amountsec, wxDefaultPosition, wxSize(100, 25),str,wxSIMPLE_BORDER);

        
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(195,195,195));
        TextCtrl2->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl2->SetForegroundColour(wxColor(195,195,195));
        amount->SetBackgroundColour(wxColor(51,51,51));
        amount->SetForegroundColour(wxColor(195,195,195));
        //add create button

        createbtn = new wxButton(this->panel_bottom, ID_Factory, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        createbtn->SetBackgroundColour(wxColor(51,51,51));
        createbtn->SetForegroundColour(wxColor(195,195,195));
        
        

        createbtn->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl2->SetMaxSize(wxSize(100, 25));
        amount->SetMaxSize(wxSize(100, 25));
        
        

        this->panelsizer->Add(TextCtrl1, 1, wxEXPAND | wxALL, 10);
        this->panelsizer->Add(TextCtrl2, 1, wxEXPAND | wxALL, 10);
        this->panelsizer->Add(amount, 1, wxEXPAND | wxALL, 10);
        this->panelsizerbot->Add(createbtn, 1, wxEXPAND | wxALL, 10);

        attributes.push_back(TextCtrl1);
        attributes.push_back(TextCtrl2);
        attributes.push_back(amount);
        
        

    }else if(event.GetString()=="Observer"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(this->panel_top, wxID_ANY, _("SubjectClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(195,195,195));

        createbtn = new wxButton( this->panel_bottom, ID_Observer, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(51,51,51));
        createbtn->SetForegroundColour(wxColor(195,195,195));
        
        
        this->panelsizer->Add(TextCtrl1, 1, wxEXPAND | wxALL, 10);
        this->panelsizerbot->Add(createbtn, 1, wxEXPAND | wxALL, 10);

        attributes.push_back(TextCtrl1);
    }


    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    this->Layout();
}

//method to build frame for new file creation
void MyFrame::BuildMenu(wxCommandEvent& event){
    
    Frame = new BuildFrame("C++ Builder", wxPoint(100, 100), wxSize(400, 400));
    Frame->SetMinSize(wxSize(400,400));
    Frame->Show();
}



//main method for gui
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



