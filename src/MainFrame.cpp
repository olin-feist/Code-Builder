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
#include "cppbuilder.h"
#include "fileEditor.h"
//enum for event id's
enum{
    newcpp = 1,
};

//event table for MainFrame||mainframe
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(newcpp,  MainFrame::BuildMenu)
    EVT_MENU(wxID_EXIT,  MainFrame::OnQuit)
    EVT_MENU(wxID_OPEN,  MainFrame::OpenFile)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
   
    this->SetBackgroundColour(wxColor(51,51,51));
    panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel_left->SetBackgroundColour(wxColor(30, 30, 30));
    

    panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel_right->SetBackgroundColour(wxColor(30, 30, 30));
    
   

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel_left, 1,wxALL |wxEXPAND, 10);
    sizer->Add(panel_right,8, wxALL | wxEXPAND, 10);

    this->SetSizerAndFit(sizer);
    
    
   
    panelsizer = new wxBoxSizer(wxVERTICAL);
    panel_left->SetSizerAndFit(panelsizer);
    
    
    
    
    //menubar
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

    file->Append(wxID_OPEN, wxT("&Open"));
    file->AppendSeparator();

    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    file->Append(quit);

    menubar->Append(file, wxT("&File"));
    SetMenuBar(menubar);

    SetMinClientSize(wxSize(800,800));
    SetMinSize(wxSize(800,800));
    sizer->SetMinSize(wxSize(800,800));
}

//method to build frame for new file creation
void MainFrame::BuildMenu(wxCommandEvent& event){
    
    BuildFrame* Frame = new BuildFrame("C++ Builder", wxPoint(100, 100), wxSize(300, 300));
    Frame->SetMinSize(wxSize(300,300));
    Frame->Show();
}

void MainFrame::OpenFile(wxCommandEvent &event){
    

    wxFileDialog dialog(this, wxEmptyString, wxEmptyString, wxEmptyString,wxFileSelectorDefaultWildcardStr); 
    dialog.ShowModal();
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


   /* wxTreeItemId rootId=filetree->AddRoot(wxT("test"));
    filetree->AppendItem(rootId, "Node 1");
    wxTreeItemId child2Id = filetree->AppendItem(rootId, "Node 2");
    filetree->AppendItem(child2Id, "Child of node 2");
    filetree->AppendItem(rootId, "Node 3");*/

    filetree->SetBackgroundColour(wxColor(30, 30, 30));
    filetree->SetForegroundColour(wxColor(195,195,195));
    filetree->SetWindowStyleFlag(wxNO_BORDER);
    
    panelsizer->Add(filetree, 1, wxALL|wxEXPAND, 10);
    panel_left->SetSizerAndFit(panelsizer);

    
    
    panel_right->Layout();
    this->Layout();
    this->Refresh();
}

void MainFrame::OnQuit(wxCommandEvent& event){

    Close(true);
}