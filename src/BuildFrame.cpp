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

//event table for buildframe
wxBEGIN_EVENT_TABLE(BuildFrame, wxFrame)
    EVT_BUTTON(ID_Factory, BuildFrame::OnFactory)
    EVT_BUTTON(ID_Observer,  BuildFrame::OnObserver)
    EVT_COMBOBOX(choiceevent,BuildFrame::choiceSelected)
    EVT_COMBOBOX(amountsec,BuildFrame::amountSelected)
wxEND_EVENT_TABLE()


BuildFrame::BuildFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_top->SetBackgroundColour(wxColor(30, 30, 30));
    
    this->SetBackgroundColour(wxColor(51,51,51));

    panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 30));
   

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10);
    sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);
    

    this->SetSizerAndFit(sizer);

    panelsizer = new wxGridSizer(2,5,5);
    panelsizerbot = new wxBoxSizer(wxVERTICAL);

    wxArrayString str;
    str.Add("Factory");
    str.Add("Observer");
    wxOwnerDrawnComboBox *wxCh = new wxOwnerDrawnComboBox(panel_top,choiceevent, wxT(""),wxDefaultPosition, wxSize(100, 25),str);

    wxCh->SetMaxSize(wxSize(100, 25));
    wxCh->ClearBackground();
    wxCh->SetTextCtrlStyle(wxSIMPLE_BORDER);
    wxCh->SetThemeEnabled(false);
    wxCh->GetTextCtrl()->SetMargins(wxCoord(5),wxCoord(5));
    wxCh->SetBackgroundColour(wxColor(51,51,51));
    wxCh->SetForegroundColour(wxColor(195,195,195));
    
    filename = new wxTextCtrl(panel_top, wxID_ANY, wxT("filenname"), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER);
    filename->SetMargins(wxPoint(5,5));
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
    wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Pattern",wxDefaultPosition, wxSize(100, 25));
    wxStaticText* label2 = new wxStaticText(panel_top, wxID_ANY,"File Name",wxDefaultPosition, wxSize(100, 25));
    wxStaticText* label3 = new wxStaticText(panel_top, wxID_ANY,"Directory",wxDefaultPosition, wxSize(100, 25));

    label1->SetForegroundColour(wxColor(195,195,195));
    label2->SetForegroundColour(wxColor(195,195,195));
    label3->SetForegroundColour(wxColor(195,195,195));

    panelsizer->Add(label1, 2, wxALL, 10);
    panelsizer->Add(wxCh, 2, wxALL, 10);
    panelsizer->Add(label2, 2, wxALL, 10);
    panelsizer->Add(filename, 2, wxALL, 10);
    panelsizer->Add(label3, 2, wxALL, 10);
    panelsizer->Add(filePickerCtrl, 2, wxALL, 10);


    createbtn = new wxButton(panel_bottom, wxID_ANY, wxT("Create"), wxDefaultPosition, wxSize(100, 25), wxNO_BORDER);
    createbtn->SetBackgroundColour(wxColor(151,151,151));
    createbtn->SetForegroundColour(wxColor(195,195,195));
    panelsizerbot->Add(createbtn, 1, wxALL, 10);  
        

        createbtn->SetMaxSize(wxSize(100, 25));
    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    

    

}

//check is there is user input if not send error(false)
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
    
    if(attributes.size()>6){
        for(int i=6;i<attributes.size();i++){
            
            attributes[i]->Destroy();
        }
        attributes.erase(attributes.begin()+6,attributes.end());
    }
    

    for(int i=0;i<=event.GetInt();i++){
        
        wxStaticText* label1 = new wxStaticText(panel_top, wxID_ANY,"Factory "+to_string(i+1),wxDefaultPosition, wxSize(100, 25));
        label1->SetForegroundColour(wxColor(195,195,195));

        wxTextCtrl *temp = new wxTextCtrl(this->panel_top, wxID_ANY, _(""), wxDefaultPosition, wxSize(100, 25), wxSIMPLE_BORDER );
        temp->SetMaxSize(wxSize(100, 25));
        temp->SetBackgroundColour(wxColor(51,51,51));
        temp->SetForegroundColour(wxColor(195,195,195));

        this->panelsizer->Add(label1, 2, wxALL, 10);
        this->panelsizer->Add(temp, 2, wxALL, 10);
        attributes.push_back(label1);
        attributes.push_back(temp);
    }
    


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


//method for handling selection of different oop patterns
void BuildFrame::choiceSelected(wxCommandEvent& event){
    for(wxControl* w: attributes){
        w->Destroy();
       
    }
    attributes.clear();
    


   
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

    }


    panel_top->SetSizerAndFit(panelsizer);
    panel_bottom->SetSizerAndFit(panelsizerbot);
    this->Layout();
}