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
#include <wx/stc/stc.h>

#include "builders/javabuilder.h"
#include "BuildFrame.h"



//enum for event id's
enum{
    ID_Factory = 1,
    ID_Observer = 2,
    choiceevent = 3,
    amountsec = 4,
    ID_Command = 5,
    ID_Singleton=6,
    ID_Desc=7
};


    
//event table for buildframe
wxBEGIN_EVENT_TABLE(buildframeJava, wxFrame)
    EVT_BUTTON(ID_Factory, buildframeJava::OnFactory)
    EVT_BUTTON(ID_Observer,  buildframeJava::OnObserver)
    EVT_BUTTON(ID_Command,  buildframeJava::OnCommand)
    EVT_BUTTON(ID_Singleton,  buildframeJava::OnSingleton)
    EVT_COMBOBOX(choiceevent,buildframeJava::choiceSelected)
    EVT_COMBOBOX(amountsec,buildframeJava::amountSelected)
wxEND_EVENT_TABLE()




//constructor for buildframe
buildframeJava::buildframeJava(const wxString &title, const wxPoint &pos, const wxSize &size):BuildFrame(title, pos, size){
    panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_right->SetBackgroundColour(wxColor(30, 30, 30));
    wxBoxSizer *sizerright = new wxBoxSizer(wxVERTICAL);
    
    
    wxStaticText* desc = new wxStaticText(panel_right, wxID_ANY,"Java Builder",wxDefaultPosition, wxDefaultSize);
    wxFont font = desc->GetFont();
    font.SetPointSize(font.GetPointSize() + 10);
    desc->SetFont(font);

    desc->SetForegroundColour(wxColor(248,152,29));

    wxStaticText* desc1 = new wxStaticText(panel_right, wxID_ANY,"Select design pattern from dropdown\n menu and fill in fields to create .java file",wxDefaultPosition, wxDefaultSize,wxTE_MULTILINE);
    desc1->SetForegroundColour(wxColor(255,255,255));
    font = desc1->GetFont();
    font.SetPointSize(font.GetPointSize() + 1);
    desc1->SetFont(font);
    wxStaticText* desc2 = new wxStaticText(panel_right, wxID_ANY,"Current Patterns:\n- Observer\n- Singleton\n- Factory\n- Command",wxDefaultPosition, wxDefaultSize);
    //desc2->Wrap(10);
    desc2->SetForegroundColour(wxColor(255,255,255));
    font = desc2->GetFont();
    font.SetPointSize(font.GetPointSize() + 1);
    desc2->SetFont(font);


  
    desc->SetBackgroundColour(wxColor(30, 30, 30));
    sizerright->Add(desc, 0.5, wxEXPAND | wxALL, 10);
    sizerright->Add(desc1, 0.5, wxEXPAND | wxALL, 10);
    sizerright->Add(desc2, 0.5, wxEXPAND | wxALL, 10);
    
    panel_right->SetSizerAndFit(sizerright);
    
    panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_left->SetBackgroundColour(wxColor(30, 30, 30));
 

    wxBoxSizer *sizermain = new wxBoxSizer(wxHORIZONTAL);
    sizermain->Add(panel_left, 1, wxEXPAND | wxALL, 10);
    sizermain->Add(panel_right, 1, wxEXPAND | wxALL, 10);
    this->SetSizerAndFit(sizermain);

    //create top panel that holds user input to build class
    panel_top = new wxPanel(panel_left, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_top->SetBackgroundColour(wxColor(30, 30, 30));
    
    //set frame color
    this->SetBackgroundColour(wxColor(51,51,51));

    //panel botton for creat btn
    panel_bottom = new wxPanel(panel_left, wxID_ANY, wxDefaultPosition, wxSize(100, 30));
   
    //sizer for frame
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    //set sizer
    panel_left->SetSizerAndFit(sizer);
    //add panels to frame sizer
    panel_left->GetSizer()->Add(panel_top, 0, wxEXPAND | wxALL, 10);
    panel_left->GetSizer()->Add(panel_bottom, 0, wxALL, 10);
    
   

    //create panel sizers for top and bot panels
    wxGridSizer *panelsizer = new wxGridSizer(2,5,5);
    wxBoxSizer *panelsizerbot= new wxBoxSizer(wxVERTICAL);
    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    
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
    panel_top->GetSizer()->Add(label1, 0, wxALL, 10);
    panel_top->GetSizer()->Add(wxCh, 0, wxALL, 10);
    panel_top->GetSizer()->Add(label2, 0, wxALL, 10);
    panel_top->GetSizer()->Add(filename, 0, wxALL, 10);
    panel_top->GetSizer()->Add(label3, 0, wxALL, 10);
    panel_top->GetSizer()->Add(filePickerCtrl, 0, wxALL, 10);

    //creat locked creat button
    createbtn = new wxButton(panel_bottom, wxID_ANY, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
    createbtn->SetBackgroundColour(wxColor(151,151,151));
    createbtn->SetForegroundColour(wxColor(195,195,195));
    panel_bottom->GetSizer()->Add(createbtn, 1, wxALL, 10);  
        
    
    createbtn->SetMaxSize(wxSize(100, 25));
    //set sizers
    panel_top->SetSizerAndFit(panel_top->GetSizer());
    panel_bottom->SetSizerAndFit(panel_bottom->GetSizer());
    

    
    panel_left->GetSizer()->SetSizeHints(panel_left);
    panel_right->GetSizer()->SetSizeHints(panel_right);
    this->GetSizer()->SetSizeHints(this);

    
}

//check is there is user input, if not send error(false)
bool buildframeJava::validateinput(vector<string> v){
   
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
void buildframeJava::amountSelected(wxCommandEvent &event){
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
        wxTextCtrl *temp = new wxTextCtrl(panel_top, wxID_ANY, _(""), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        temp->SetMaxSize(wxSize(100, 25));
        temp->SetBackgroundColour(wxColor(51,51,51));
        temp->SetForegroundColour(wxColor(195,195,195));

        //add to sizer and push to list
        panel_top->GetSizer()->Add(label1, 2, wxALL, 10);
        panel_top->GetSizer()->Add(temp, 2, wxALL, 10);
        attributes.push_back(label1);
        attributes.push_back(temp);
    }
    

    //layout reset
    panel_top->SetSizerAndFit(panel_top->GetSizer());
    
    panel_top->Layout();
    this->Layout();
    this->Refresh();
    panel_right->Layout();
    panel_left->GetSizer()->SetSizeHints(panel_left);
    panel_right->GetSizer()->SetSizeHints(panel_right);
    this->GetSizer()->SetSizeHints(this);
}

//create factory java on call
void buildframeJava::OnFactory(wxCommandEvent &event){
    
    
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
        javabuilder::writeFile(javabuilder::factorybuilder(headname,methodname,v),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
    
    

}

//create observer java on call
void buildframeJava::OnObserver(wxCommandEvent& event){
    
    string classname;
    classname=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();

    vector<string> test;
    test.push_back(classname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());
    if(validateinput(test)){
        javabuilder::writeFile( javabuilder::observerbuilder(classname),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }

}

//create command java on call
void buildframeJava::OnCommand(wxCommandEvent& event){
    
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
        javabuilder::writeFile(javabuilder::commandbuilder(refclass,invokerclass,classnames),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
}

//create singleton java on call
void buildframeJava::OnSingleton(wxCommandEvent& event){
  
        
    string classname;
    classname=((wxTextCtrl*) attributes[1])->GetValue().ToStdString();

    vector<string> test;
    test.push_back(classname);
    test.push_back(filePickerCtrl->GetPath().ToStdString());
    test.push_back(filename->GetValue().ToStdString());
    if(validateinput(test)){
        javabuilder::writeFile( javabuilder::singletonbuilder(classname),filePickerCtrl->GetPath().ToStdString(),filename->GetValue().ToStdString());
        Close(true);
    }
}


//method for handling selection of different oop patterns
void buildframeJava::choiceSelected(wxCommandEvent& event){
    for(wxControl* w: attributes){
        w->Destroy();
       
    }
    attributes.clear();
    


    //factory
    if(event.GetString()=="Factory"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(panel_top, wxID_ANY, wxT("MainInterface"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        TextCtrl1->SetMargins(wxPoint(5,5));
        wxTextCtrl *TextCtrl2 = new wxTextCtrl(panel_top, wxID_ANY, wxT("MethodName"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
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
        createbtn = new wxButton(panel_bottom, ID_Factory, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetBackgroundColour(wxColor(248,152,29));
        createbtn->SetForegroundColour(wxColor(255,255,255));
        
        

        createbtn->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl2->SetMaxSize(wxSize(100, 25));
        amount->SetMaxSize(wxSize(100, 25));
        
        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Main Interface",wxDefaultPosition, wxSize(100, 25));
        wxStaticText* label2 = new wxStaticText(panel_top, wxID_ANY,"Method Name",wxDefaultPosition, wxSize(100, 25));
        wxStaticText* label3 = new wxStaticText(panel_top, wxID_ANY,"Number Factories",wxDefaultPosition, wxSize(100, 25));
        

        label1->SetForegroundColour(wxColor(195,195,195));
        label2->SetForegroundColour(wxColor(195,195,195));
        label3->SetForegroundColour(wxColor(195,195,195));
        
        panel_top->GetSizer()->Add(label1, 0, wxALL, 10);
        panel_top->GetSizer()->Add(TextCtrl1, 0, wxALL, 10);
        panel_top->GetSizer()->Add(label2, 0, wxALL, 10);
        panel_top->GetSizer()->Add(TextCtrl2, 0, wxALL, 10);
        panel_top->GetSizer()->Add(label3, 0, wxALL, 10);
        panel_top->GetSizer()->Add(amount, 0, wxALL, 10);

        panel_bottom->GetSizer()->Add(createbtn, 0, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
        attributes.push_back(label2);
        attributes.push_back(TextCtrl2);
        attributes.push_back(label3);
        attributes.push_back(amount);
        
        
    //Observer
    }else if(event.GetString()=="Observer"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(panel_top, wxID_ANY, _("SubjectClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(255,255,255));

        createbtn->Destroy();
        createbtn = new wxButton( panel_bottom, ID_Observer, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(248,152,29));
        createbtn->SetForegroundColour(wxColor(255,255,255));

        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Subject Class",wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        panel_top->GetSizer()->Add(label1, 0, wxALL, 10);
        panel_top->GetSizer()->Add(TextCtrl1, 0, wxALL, 10);

        panel_bottom->GetSizer()->Add(createbtn, 0, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
    //Command
    }else if(event.GetString()=="Command"){

        wxTextCtrl *TextCtrl1 = new wxTextCtrl(panel_top, wxID_ANY, _("ReceiverClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(255,255,255));

        wxTextCtrl *TextCtrl2 = new wxTextCtrl(panel_top, wxID_ANY, _("InvokerClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
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
        createbtn = new wxButton( panel_bottom, ID_Command, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(248,152,29));
        createbtn->SetForegroundColour(wxColor(255,255,255));



        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Receiver Class",wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        wxStaticText* label2 = new wxStaticText(panel_top, wxID_ANY,"Command Classes",wxDefaultPosition, wxSize(100, 25));
        label2->SetForegroundColour(wxColor(195,195,195));

        wxStaticText* label3 = new wxStaticText(panel_top, wxID_ANY,"Invoker Class",wxDefaultPosition, wxSize(100, 25));
        label3->SetForegroundColour(wxColor(195,195,195));

        panel_top->GetSizer()->Add(label1, 0, wxALL, 10);
        panel_top->GetSizer()->Add(TextCtrl1, 0, wxALL, 10);
        panel_top->GetSizer()->Add(label3, 0, wxALL, 10);
        panel_top->GetSizer()->Add(TextCtrl2, 0, wxALL, 10);
        panel_top->GetSizer()->Add(label2, 0, wxALL, 10);
        panel_top->GetSizer()->Add(amount, 0, wxALL, 10);

        panel_bottom->GetSizer()->Add(createbtn, 0, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
        attributes.push_back(label3);
        attributes.push_back(TextCtrl2);
        attributes.push_back(label2);
        attributes.push_back(amount);

        
    //Singleton
    }else if(event.GetString()=="Singleton"){
        wxTextCtrl *TextCtrl1 = new wxTextCtrl(panel_top, wxID_ANY, _("SingletonClass"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
        TextCtrl1->SetMaxSize(wxSize(100, 25));
        TextCtrl1->SetBackgroundColour(wxColor(51,51,51));
        TextCtrl1->SetForegroundColour(wxColor(255,255,255));

        createbtn->Destroy();
        createbtn = new wxButton( panel_bottom, ID_Singleton, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
        createbtn->SetMaxSize(wxSize(100, 25));
        createbtn->SetBackgroundColour(wxColor(248,152,29));
        createbtn->SetForegroundColour(wxColor(255,255,255));

        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Class Name",wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        panel_top->GetSizer()->Add(label1, 0, wxALL, 10);
        panel_top->GetSizer()->Add(TextCtrl1, 0, wxALL, 10);

        panel_bottom->GetSizer()->Add(createbtn, 0, wxEXPAND | wxALL, 10);

        attributes.push_back(label1);
        attributes.push_back(TextCtrl1);
    }


    panel_top->SetSizerAndFit(panel_top->GetSizer());
    panel_bottom->SetSizerAndFit(panel_bottom->GetSizer());


    panel_left->GetSizer()->SetSizeHints(panel_left);
    panel_right->GetSizer()->SetSizeHints(panel_right);
    this->GetSizer()->SetSizeHints(this);

    this->Layout();
    this->Refresh();

}



