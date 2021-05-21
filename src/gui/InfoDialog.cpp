#include "InfoDialog.h"

//event table for buildframe
wxBEGIN_EVENT_TABLE(InfoDialog, wxDialog)
    EVT_BUTTON(wxID_EXIT, InfoDialog::OnQuit)
wxEND_EVENT_TABLE()


InfoDialog::InfoDialog(const wxString & title)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(250, 300))
{
    SetBackgroundColour(wxColor(30, 30, 30));
    wxPanel *panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* desc = new wxStaticText(panel, wxID_ANY,"Class Repairer",wxDefaultPosition, wxDefaultSize);
    wxFont font = desc->GetFont();
    font.SetPointSize(font.GetPointSize() + 10);
    desc->SetFont(font);

    desc->SetForegroundColour(wxColor(0,122,204));

    wxStaticText* desc1 = new wxStaticText(panel, wxID_ANY,"-Will find all class attributes and add\ngetters and setters.",wxDefaultPosition, wxDefaultSize,wxTE_MULTILINE);
    desc1->SetForegroundColour(wxColor(255,255,255));
    font = desc1->GetFont();
    font.SetPointSize(font.GetPointSize() + 1);
    desc1->SetFont(font);
    wxStaticText* desc2 = new wxStaticText(panel, wxID_ANY,"-Currently only avalible for python\n and java files",wxDefaultPosition, wxDefaultSize);
    
    desc2->SetForegroundColour(wxColor(255,255,255));
    font = desc2->GetFont();
    font.SetPointSize(font.GetPointSize() + 1);
    desc2->SetFont(font);

    wxStaticText* desc3 = new wxStaticText(panel, wxID_ANY,"-Java files need to be compilable and\n python files need to have tabs",wxDefaultPosition, wxDefaultSize);
    
    desc3->SetForegroundColour(wxColor(255,255,255));
    font = desc3->GetFont();
    font.SetPointSize(font.GetPointSize() + 1);
    desc3->SetFont(font);

    wxButton *closeButton = new wxButton(panel, wxID_EXIT, wxT("Close"), wxDefaultPosition, wxSize(100, 25));
    closeButton->SetBackgroundColour(wxColor(14,99,156));
    closeButton->SetForegroundColour(wxColor(255,255,255));

    vbox->Add(desc, 0.5, wxEXPAND | wxALL, 10);
    vbox->Add(desc1, 0.5, wxEXPAND | wxALL, 10);
    vbox->Add(desc2, 0.5, wxEXPAND | wxALL, 10);
    vbox->Add(desc3, 0.5, wxEXPAND | wxALL, 10);
    vbox->Add(closeButton, 0.5, wxALL, 10);

    panel->SetSizerAndFit(vbox);

  Centre();
  ShowModal();

  Destroy(); 
}

void InfoDialog::OnQuit(wxCommandEvent& event){
    Close(true);
}