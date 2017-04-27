#if 0

#include "wx/wx.h"
#include "wx/caret.h"

class Panel : public wxPanel {
  wxDECLARE_EVENT_TABLE();
public:
  Panel(wxWindow* parent) {
  SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
  wxPanel::Create(parent,
                 wxID_ANY,
                 wxDefaultPosition,
                 wxDefaultSize,
                 wxBORDER_NONE | wxTRANSPARENT_WINDOW);
  }

  void OnLD(wxMouseEvent& e) {
    wxMessageBox("");
  }
};

wxBEGIN_EVENT_TABLE(Panel, wxPanel)
EVT_LEFT_DOWN(Panel::OnLD)
wxEND_EVENT_TABLE()

class MainFrame : public wxFrame {
  wxDECLARE_EVENT_TABLE();
public:
  MainFrame() {};
  bool Create(const wxString& title) {
    wxFrame::Create(NULL, wxID_ANY, title);
    //wxButton* button = new wxButton(this, wxID_OK);
    //wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    //vsizer->Add(button, 1, wxEXPAND | wxALL, 50);

    wxString label = _("asddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddf");
    text_ = new wxStaticText(this, 123, label, wxDefaultPosition, wxSize(200, 200));
    text_->SetWindowStyle(wxST_ELLIPSIZE_END);
    text_->SetBackgroundColour(*wxWHITE);
    text_->Wrap(100);

    //wxButton* button = new wxButton(this, wxID_PASTE, _("123"));

    //wxButton* button_ = new wxButton(this, wxID_PASTE, _("1234"));

    wxPanel* text = new Panel(this);
    //text->SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
    //text->Create(this,
    //             wxID_ANY,
    //             wxDefaultPosition,
    //             wxDefaultSize,
    //             wxBORDER_NONE | wxTRANSPARENT_WINDOW);
    //wxColor* a = new wxColor(255, 255, 255, 0);

    //text->SetBackgroundColour(wxTransparentColor);
    text->SetSize(wxSize(100 , 103));
    text->SetTransparent(1);
   
    bool is_t = text->CanSetTransparent();

    wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    vsizer->Add(text, 1, wxEXPAND | wxALL, 50);
    SetSizer(vsizer);
    //Connect(wxID_OPEN, wxEVT_LEFT_DOWN, wxMouseEventHandler(MainFrame::OnMouseLeftDown));
    Connect(wxID_OPEN, wxEVT_COMMAND_LEFT_CLICK, wxCommandEventHandler(MainFrame::OnButtonClick));




    return true;
  }

  void OnOk(wxCommandEvent& evt) {
    wxMessageBox(wxT("Hello, world!"));
  }

  void OnMouseLeftDown(wxMouseEvent& evt) {
    //wxRect rect = text_->GetRect();
    //if (rect.Contains(evt.GetPosition())) {
    //  wxMessageBox("in");
    //}
    wxMessageBox("out");

  }

  void OnButtonClick(wxCommandEvent& evt) {
    wxMessageBox("");
  }

private:
  wxStaticText* text_;
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(wxID_OK, MainFrame::OnOk)
EVT_LEFT_DOWN(MainFrame::OnMouseLeftDown)
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



