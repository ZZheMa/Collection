#if 0

#include "wx/wx.h"

enum PopMenuId {
  Menu_Popup_Id1 = 0,
  Menu_Popup_Id2,
  Menu_Popup_Id3,
};

class MainFrame : public wxFrame {
  wxDECLARE_EVENT_TABLE();
public:
  MainFrame() {};
  bool Create(const wxString& title) {
    wxFrame::Create(NULL, wxID_ANY, title);
    wxButton* button = new wxButton(this, wxID_OK);
    wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    vsizer->Add(button, 1, wxEXPAND | wxALL, 50);
    SetSizer(vsizer);
    return true;
  }

private:
  void OnOk(wxCommandEvent& evt) {
    wxMessageBox(wxT("Hello, world!"));
  }

  void OnRightClick(wxMouseEvent& evt) {
    wxMenu menu;
    menu.Append(Menu_Popup_Id1, wxT("menu&1"));
    menu.Append(Menu_Popup_Id2, wxT("menu&2"));
    menu.Append(Menu_Popup_Id3, wxT("menu&3"));

    PopupMenu(&menu, evt.GetPosition());
  }

  void OnPopMenu1(wxCommandEvent& evt) {
    wxMessageBox(wxT("1"));
  }
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(wxID_OK, MainFrame::OnOk)
EVT_MENU(Menu_Popup_Id1, MainFrame::OnPopMenu1)
EVT_RIGHT_UP(MainFrame::OnRightClick)
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
