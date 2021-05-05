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


#include "cppbuilder.h"
#include "BuildFrame.h"

//enum for event id's
enum{
    ID_Factory = 1,
    ID_Observer = 2,
    choiceevent = 3,
    amountsec = 4,
    ID_Command = 5,
    ID_Singleton=6
};

//event table for buildframe
wxBEGIN_EVENT_TABLE(BuildFrame, wxFrame)
    EVT_BUTTON(ID_Factory, BuildFrame::OnFactory)
    EVT_BUTTON(ID_Observer,  BuildFrame::OnObserver)
    EVT_BUTTON(ID_Command,  BuildFrame::OnCommand)
    EVT_BUTTON(ID_Singleton,  BuildFrame::OnSingleton)
    EVT_COMBOBOX(choiceevent,BuildFrame::choiceSelected)
    EVT_COMBOBOX(amountsec,BuildFrame::amountSelected)
wxEND_EVENT_TABLE()

//constructor for buildframe
BuildFrame::BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
    //create top panel that holds user input to build class
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_top->SetBackgroundColour(wxColor(30, 30, 30));
    
    //set frame color
    this->SetBackgroundColour(wxColor(51,51,51));

    //panel botton for creat btn
    panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 30));
   
    //sizer for frame
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    //add panels to frame sizer
    sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10);
    sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);
    
    //set sizer
    this->SetSizerAndFit(sizer);

    //create panel sizers for top and bot panels
    panelsizer = new wxGridSizer(2,5,5);
    panelsizerbot = new wxBoxSizer(wxVERTICAL);

    //create drop down menu for selecting design types
    wxArrayString str;
    str.Add("Factory");
    str.Add("Observer");
    str.Add("Command");
    str.Add("Singleton");
    wxOwnerDrawnComboBox *wxCh = new wxOwnerDrawnComboBox(panel_top,choiceevent, wxT(""),wxDefaultPosition, wxSize(100, 25),str);
    //format choice box
    wxCh->SetMaxSize(wxSize(100, 25));
    wxCh->ClearBackground();
    wxCh->SetTextCtrlStyle(wxSIMPLE_BORDER);
    wxCh->SetThemeEnabled(false);
    wxCh->GetTextCtrl()->SetMargins(wxCoord(5),wxCoord(5));
    wxCh->SetBackgroundColour(wxColor(51,51,51));
    wxCh->SetForegroundColour(wxColor(195,195,195));
    
    //input for file name
    filename = new wxTextCtrl(panel_top, wxID_ANY, wxT("filename"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
    filename->SetMargins(wxPoint(5,5));
    filename->SetBackgroundColour(wxColor(51,51,51));
    filename->SetForegroundColour(wxColor(195,195,195));

    //input for file path selection
    filePickerCtrl = new wxDirPickerCtrl(panel_top, wxID_ANY,wxEmptyString,wxDirSelectorPromptStr,wxDefaultPosition, wxSize(100, 25),wxDIRP_SMALL | wxDIRP_USE_TEXTCTRL);

    //customize directory picker
    wxTextCtrl *dirtext=filePickerCtrl->GetTextCtrl();
    dirtext->SetBackgroundColour(wxColor(51,51,51));
    dirtext->SetForegroundColour(wxColor(195,195,195));
    dirtext->SetWindowStyleFlag(wxSIMPLE_BORDER);
    wxButton *btn = (wxButton*) filePickerCtrl->GetPickerCtrl();
    btn->SetBackgroundColour(wxColor(51,51,51));
    btn->SetForegroundColour(wxColor(195,195,195));
    btn->SetWindowStyleFlag(wxBORDER_NONE);
    btn->SetMaxSize(wxSize(25,25));

    //set color
    filename->SetMaxSize(wxSize(100, 25));
    filePickerCtrl->SetMaxSize(wxSize(250, 25));

    //create lables
    wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Pattern",wxDefaultPosition, wxSize(100, 25));
    wxStaticText* label2 = new wxStaticText(panel_top, wxID_ANY,"File Name",wxDefaultPosition, wxSize(100, 25));
    wxStaticText* label3 = new wxStaticText(panel_top, wxID_ANY,"Directory",wxDefaultPosition, wxSize(100, 25));
    //label color
    label1->SetForegroundColour(wxColor(195,195,195));
    label2->SetForegroundColour(wxColor(195,195,195));
    label3->SetForegroundColour(wxColor(195,195,195));

    //add elements
    panelsizer->Add(label1, 2, wxALL, 10);
    panelsizer->Add(wxCh, 2, wxALL, 10);
    panelsizer->Add(label2, 2, wxALL, 10);
    panelsizer->Add(filename, 2, wxALL, 10);
    panelsizer->Add(label3, 2, wxALL, 10);
    panelsizer->Add(filePickerCtrl, 2, wxALL, 10);

    //creat locked creat button
    createbtn = new wxButton(panel_bottom, wxID_ANY, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
    createbtn->SetBackgroundColour(wxColor(151,151,151));
    createbtn->SetForegroundColour(wxColor(195,195,195));
    panelsizerbot->Add(createbtn, 1, wxALL, 10);  
        
    
    createbtn->SetMaxSize(wxSize(100, 25));
    //set sizers
    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    

    

}

//check is there is user input, if not send error(false)
bool BuildFrame::validateinput(vector<string> v){
   
    for(string s: v){
       
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
    //delete attributes from previous 
    if(attributes.size()>6){
        for(int i=6;i<attributes.size();i++){
            
            attributes[i]->Destroy();
        }
        attributes.erase(attributes.begin()+6,attributes.end());
    }
    
    //create new input based on number
    for(int i=0;i<=event.GetInt();i++){
        //label
        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Class "+to_string(i+1),wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        //text input
        wxTextCtrl *temp = new wxTextCtrl(this->panel_top, wxID_ANY, _(""), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        temp->SetMaxSize(wxSize(100, 25));
        temp->SetBackgroundColour(wxColor(51,51,51));
        temp->SetForegroundColour(wxColor(195,195,195));

        //add to sizer and push to list
        this->panelsizer->Add(label1, 2, wxALL, 10);
        this->panelsizer->Add(temp, 2, wxALL, 10);
        attributes.push_back(label1);
        attributes.push_back(temp);
    }
    

    //layout reset
    this->panel_top->SetSizerAndFit(panelsizer);
    this->Layout();
    panel_top->Layout();
}

//create factory c++ on call
void BuildFrame::OnFactory(wxCommandEvent &event){
    
    
    string headname;
    string methodname;
    headname=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();
    methodname=((wxTextCtrl*) attributes[3])->GetValue().ToStdString();
    vector<string> test;
    test.push_back(headname);
    test.push_back(methodname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());

    

    vector<string> v;
    for(int i=7;i<attributes.size();i+=2){
       
        v.push_back(((wxTextCtrl*) attributes[i])->GetValue().ToStdString());
       
    }
    
    //test.insert(test.end(),v.begin(),v.end());
    if(validateinput(test)){
        cppbuilder::writeFile(cppbuilder::factorybuilder(headname,methodname,v),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
    
    

}

//create observer c++ on call
void BuildFrame::OnObserver(wxCommandEvent& event){
    
    string classname;
    classname=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();

    vector<string> test;
    test.push_back(classname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());
    if(validateinput(test)){
        cppbuilder::writeFile( cppbuilder::observerbuilder(classname),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }

}

//create command c++ on call
void BuildFrame::OnCommand(wxCommandEvent& event){
    
    string refclass;
    string invokerclass;
    vector<string> classnames;

    refclass=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();
    invokerclass=((wxTextCtrl*) attributes[3])->GetValue().ToStdString();

    vector<string> test;
    test.push_back(refclass);
    test.push_back(invokerclass);

    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());

    for(int i=7;i<attributes.size();i+=2){
        cout<<((wxTextCtrl*) attributes[i])->GetValue().ToStdString()<<endl;
        classnames.push_back(((wxTextCtrl*) attributes[i])->GetValue().ToStdString());
    }

    cout<<refclass<<endl;
    cout<<invokerclass<<endl;
    cout<<filePickerCtrl->GetPath().ToStdString()<<endl;
    cout<<filename->GetValue().ToStdString()<<endl;

    test.insert(test.end(),classnames.begin(),classnames.end());
    if(validateinput(test)){
        cppbuilder::writeFile(cppbuilder::commandbuilder(refclass,invokerclass,classnames),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
}

//create singleton c++ on call
void BuildFrame::OnSingleton(wxCommandEvent& event){
  
        
    string classname;
    classname=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();

    vector<string> test;
    test.push_back(classname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());
    if(validateinput(test)){
        cppbuilder::writeFile( cppbuilder::singletonbuilder(classname),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
}


//method for handling selection of different oop patterns
void BuildFrame::choiceSelected(wxCommandEvent& event){
    for(wxControl* w: attributes){
        w->Destroy();
       
    }
    attributes.clear();
    


    //factory
    if(event.GetString()=="Factory"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(this->panel_top, wxID_ANY, wxT("MainClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        TextCtrl1->SetMargins(wxPoint(5,5));
        wxTextCtrl *TextCtrl2 = new wxTextCtrl(this->panel_top, wxID_ANY, wxT("MethodName"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        TextCtrl2->SetMargins(wxPoint(5,5));
        wxArrayString str;
        str.Add("1");
        str.Add("2");
        str.Add("3");
        str.Add("4");
        str.Add("5");
        str.Add("6");
        wxOwnerDrawnComboBox  *amount = new wxOwnerDrawnComboBox(panel_top, amountsec, wxT(""), wxDefaultPosition, wxSize(100, 25),str);
        amount->ClearBackground();
        amount->SetTextCtrlStyle(wxSIMPLE_BORDER);
        amount->SetThemeEnabled(false);
        amount->GetTextCtrl()->SetMargins(wxCoord(5),wxCoord(5));
        amount->SetBackgroundColour(wxColor(51,51,51));
        amount->SetForegroundColour(wxColor(195,195,195));
        
        
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(195,195,195));
        TextCtrl2->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl2->SetForegroundColour(wxColor(195,195,195));
        
        //add create button
        createbtn->Destroy();
        createbtn = new wxButton(this->panel_bottom, ID_Factory, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetBackgroundColour(wxColor(14,99,156));
        createbtn->SetForegroundColour(wxColor(255,255,255));
        
        

        createbtn->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl2->SetMaxSize(wxSize(100, 25));
        amount->SetMaxSize(wxSize(100, 25));
        
        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Main Class",wxDefaultPosition, wxSize(100, 25));
        wxStaticText* label2 = new wxStaticText(panel_top, wxID_ANY,"Method Name",wxDefaultPosition, wxSize(100, 25));
        wxStaticText* label3 = new wxStaticText(panel_top, wxID_ANY,"Number Factories",wxDefaultPosition, wxSize(100, 25));
        

        label1->SetForegroundColour(wxColor(195,195,195));
        label2->SetForegroundColour(wxColor(195,195,195));
        label3->SetForegroundColour(wxColor(195,195,195));
        
        this->panelsizer->Add(label1, 2, wxALL, 10);
        this->panelsizer->Add(TextCtrl1, 2, wxALL, 10);
        this->panelsizer->Add(label2, 2, wxALL, 10);
        this->panelsizer->Add(TextCtrl2, 2, wxALL, 10);
        this->panelsizer->Add(label3, 2, wxALL, 10);
        this->panelsizer->Add(amount, 2, wxALL, 10);

        this->panelsizerbot->Add(createbtn, 1, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
        attributes.push_back(label2);
        attributes.push_back(TextCtrl2);
        attributes.push_back(label3);
        attributes.push_back(amount);
        
        
    //Observer
    }else if(event.GetString()=="Observer"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(this->panel_top, wxID_ANY, _("SubjectClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(255,255,255));

        createbtn->Destroy();
        createbtn = new wxButton( this->panel_bottom, ID_Observer, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(14,99,156));
        createbtn->SetForegroundColour(wxColor(255,255,255));

        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Subject Class",wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        this->panelsizer->Add(label1, 2, wxALL, 10);
        this->panelsizer->Add(TextCtrl1, 2, wxALL, 10);

        this->panelsizerbot->Add(createbtn, 1, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
    //Command
    }else if(event.GetString()=="Command"){

        wxTextCtrl *TextCtrl1 = new wxTextCtrl(this->panel_top, wxID_ANY, _("ReceiverClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(255,255,255));

        wxTextCtrl *TextCtrl2 = new wxTextCtrl(this->panel_top, wxID_ANY, _("InvokerClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl2->SetMaxSize(wxSize(100, 25));
        TextCtrl2->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl2->SetForegroundColour(wxColor(255,255,255));

       
        

        wxArrayString str;
        str.Add("1");
        str.Add("2");
        str.Add("3");
        str.Add("4");
        str.Add("5");
        str.Add("6");
        wxOwnerDrawnComboBox  *amount = new wxOwnerDrawnComboBox(panel_top, amountsec, wxT(""), wxDefaultPosition, wxSize(100, 25),str);
        amount->ClearBackground();
        amount->SetTextCtrlStyle(wxSIMPLE_BORDER);
        amount->SetThemeEnabled(false);
        amount->GetTextCtrl()->SetMargins(wxCoord(5),wxCoord(5));
        amount->SetBackgroundColour(wxColor(51,51,51));
        amount->SetForegroundColour(wxColor(195,195,195));


        createbtn->Destroy();
        createbtn = new wxButton( this->panel_bottom, ID_Command, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(14,99,156));
        createbtn->SetForegroundColour(wxColor(255,255,255));



        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Receiver Class",wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        wxStaticText* label2 = new wxStaticText(panel_top, wxID_ANY,"Command Classes",wxDefaultPosition, wxSize(100, 25));
        label2->SetForegroundColour(wxColor(195,195,195));

        wxStaticText* label3 = new wxStaticText(panel_top, wxID_ANY,"Invoker Class",wxDefaultPosition, wxSize(100, 25));
        label3->SetForegroundColour(wxColor(195,195,195));

        this->panelsizer->Add(label1, 2, wxALL, 10);
        this->panelsizer->Add(TextCtrl1, 2, wxALL, 10);
        this->panelsizer->Add(label3, 2, wxALL, 10);
        this->panelsizer->Add(TextCtrl2, 2, wxALL, 10);
        this->panelsizer->Add(label2, 2, wxALL, 10);
        this->panelsizer->Add(amount, 2, wxALL, 10);

        this->panelsizerbot->Add(createbtn, 1, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
        attributes.push_back(label3);
        attributes.push_back(TextCtrl2);
        attributes.push_back(label2);
        attributes.push_back(amount);

        
    //Singleton
    }else if(event.GetString()=="Singleton"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(this->panel_top, wxID_ANY, _("SingletonClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(255,255,255));

        createbtn->Destroy();
        createbtn = new wxButton( this->panel_bottom, ID_Singleton, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(14,99,156));
        createbtn->SetForegroundColour(wxColor(255,255,255));

        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Class Name",wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        this->panelsizer->Add(label1, 2, wxALL, 10);
        this->panelsizer->Add(TextCtrl1, 2, wxALL, 10);

        this->panelsizerbot->Add(createbtn, 1, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
    }


    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    this->Layout();
}

