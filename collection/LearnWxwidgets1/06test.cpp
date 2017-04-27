#if 0

#include "wx/wx.h"
#include "wx/statline.h"
#include "06personal_record_dialog.h"

class MainFrame : public wxFrame {
  wxDECLARE_EVENT_TABLE();
public:
  MainFrame() {};
  bool Create(const wxString& title) {
    wxFrame::Create(NULL, wxID_ANY, title);
    wxButton* button = new wxButton(this, wxID_OK);
    wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    wxStaticLine* line = new wxStaticLine(this, wxID_ANY);
    vsizer->Add(line, 1, wxEXPAND);

    vsizer->Add(button, 1, wxEXPAND | wxALL, 50);
    SetSizer(vsizer);
    return true;
  }

  void OnOk(wxCommandEvent& evt) {
    Person person;
    person.age = 17;
    person.is_vote = false;
    person.name = _("xixi");
    person.sex = _("Female");

    PersonalRecordDialog person_record_dialog(&person);
    person_record_dialog.Create(this, wxID_ANY, _("Personal Record"));
    person_record_dialog.ShowModal();
  }
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(wxID_OK, MainFrame::OnOk)
wxEND_EVENT_TABLE()

class App : public wxApp {
public:
  virtual bool OnInit() override;
  virtual int OnExit() override;
};

wxDECLARE_APP(App);
wxIMPLEMENT_APP(App);

bool App::OnInit() {
  wxApp::OnInit();

  MainFrame* main_frame = new MainFrame();
  main_frame->Create(wxT("Hello World!"));
  main_frame->Show(true);

  return true;
}

int App::OnExit() {
  wxApp::OnExit();

  return 0;
}

#endif
