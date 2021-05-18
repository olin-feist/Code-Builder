#include <iostream>
#include <vector>
#include <fstream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/wx.h>
#include <wx/dirctrl.h>

#include "MainFrame.h"
#include "BuildFrame.h"
#include "fileEditor.h"



//enum for event id's
enum{
    newcpp = 1,
    newjava=2,
    newpython=3,
    ID_Dev=4,
    ID_Setters=5,
    ID_Getters=6
};

//event table for MainFrame||mainframe
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(newcpp,  MainFrame::BuildMenuCpp)
    EVT_MENU(newjava,  MainFrame::BuildMenuJava)
    EVT_MENU(newpython,  MainFrame::BuildMenuPython)
    EVT_MENU(wxID_EXIT,  MainFrame::OnQuit)
    EVT_MENU(wxID_OPEN,  MainFrame::OpenFile)
    EVT_MENU(ID_Dev,  MainFrame::OpenConsole)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
   
    this->SetBackgroundColour(wxColor(51,51,51));
    panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel_left->SetBackgroundColour(wxColor(30, 30, 30));
    

    panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel_right->SetBackgroundColour(wxColor(30, 30, 30));
    
   

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel_left, 1,wxALL |wxEXPAND, 10);
    sizer->Add(panel_right,6, wxALL | wxEXPAND, 10);

    this->SetSizerAndFit(sizer);
    
    
   
    wxBoxSizer *panelsizer = new wxBoxSizer(wxVERTICAL);
    panel_left->SetSizerAndFit(panelsizer);
    
    
    
    
    //menubar
    wxMenuBar *menubar;
    wxMenu *file;
    wxMenuItem *quit;

    

    menubar = new wxMenuBar;
    //file menu
    file = new wxMenu;
    wxMenu* newFile = new wxMenu;

    //new file submenu
    newFile->Append(newcpp, wxT("C++"));
    newFile->Append(newjava, wxT("Java"));
    newFile->Append(newpython, wxT("Python"));
    file->AppendSubMenu(newFile, wxT("New File"));

    file->Append(wxID_OPEN, wxT("&Open"));
    file->AppendSeparator();

    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    file->Append(quit);
    
    menubar->Append(file, wxT("&File"));
    
    //options menu
    wxMenu *options = new wxMenu;
    options->Append(ID_Dev, wxT("&Close Console"));
    menubar->Append(options, wxT("&Options"));

    //repair menu
    wxMenu *repair = new wxMenu;
    repair->Append(ID_Setters, wxT("&Add Getters"));
    repair->Append(ID_Getters, wxT("&Add Setters"));
    menubar->Append(repair, wxT("&Repair"));
    repair->Enable(ID_Setters, false);
    repair->Enable(ID_Getters, false);
    //set menu bar
    SetMenuBar(menubar);


    

    SetMinClientSize(wxSize(800,800));
    SetMinSize(wxSize(800,800));
    sizer->SetMinSize(wxSize(800,800));


}

//method to build frame for new file creation
void MainFrame::BuildMenuCpp(wxCommandEvent& event){
    
    BuildFrame* Frame = new buildframec("C++ Builder", wxPoint(100, 100), wxSize(300, 300));
    Frame->SetMinSize(wxSize(300,300));
    Frame->Show();

}

void MainFrame::BuildMenuJava(wxCommandEvent& event){
    
    BuildFrame* Frame = new buildframeJava("Java Builder", wxPoint(100, 100), wxSize(300, 300));
    Frame->SetMinSize(wxSize(300,300));
    Frame->Show();
}

void MainFrame::BuildMenuPython(wxCommandEvent& event){
    
    BuildFrame* Frame = new buildframePy("Python Builder", wxPoint(100, 100), wxSize(300, 300));
    Frame->SetMinSize(wxSize(300,300));
    Frame->Show();
}

void MainFrame::OpenConsole(wxCommandEvent& event){
    FreeConsole();
}

void MainFrame::OpenFile(wxCommandEvent &event){
    

    wxFileDialog dialog(this, wxEmptyString, wxEmptyString, wxEmptyString,wxFileSelectorDefaultWildcardStr); 
    dialog.ShowModal();
    if(!(dialog.GetPath().IsNull())){

    
    wxString filename = dialog.GetPath();
    textedit->Destroy();
    textedit = new wxTextCtrl(panel_right, wxID_ANY, wxEmptyString, wxDefaultPosition,wxSize(200,200), 
    wxVSCROLL | wxHSCROLL | wxBORDER_NONE | wxWANTS_CHARS|wxTE_MULTILINE);
    textedit->SetBackgroundColour(wxColor(30, 30, 30));
    textedit->SetForegroundColour(wxColor(195,195,195));
    textedit->LoadFile(filename,wxTEXT_TYPE_ANY);

    //set font size
    wxFont font = textedit->GetFont();
    font.SetPointSize(font.GetPointSize() + 4);
    textedit->SetFont(font);

    //file tree
    wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
    sizer -> Add(textedit, 1, wxALL|wxEXPAND);
    panel_right -> SetSizer(sizer);

    filetree->Destroy();

    filetree = new wxTreeCtrl(
        panel_left,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxTR_DEFAULT_STYLE
    );
    filetree=fileEditor::getClassTree(string(filename.mb_str()),filetree);


    filetree->SetBackgroundColour(wxColor(30, 30, 30));
    filetree->SetForegroundColour(wxColor(195,195,195));
    filetree->SetWindowStyleFlag(wxNO_BORDER);
    
    panel_left->GetSizer()->Add(filetree, 1, wxALL|wxEXPAND, 10);
    
    //enable repair
    GetMenuBar()->GetMenu(2)->Enable(ID_Setters, true);
    GetMenuBar()->GetMenu(2)->Enable(ID_Getters, true);

    
    this->Layout();
    panel_right->Layout();

    }
}

void MainFrame::OnQuit(wxCommandEvent& event){

    Close(true);
}