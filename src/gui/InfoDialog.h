#include <wx/wx.h>

class InfoDialog : public wxDialog
{
public:
  InfoDialog(const wxString& title);
  void OnQuit(wxCommandEvent& event);
  wxDECLARE_EVENT_TABLE();

};