#if 0

#include "wx/wx.h"
#include "wx/splitter.h"

enum {
  ID_PANEL1 = 1,
  ID_PANEL2,
};

// 1. 自定义一个EventType，可以用在转发消息，重新包装一下消息。
wxDECLARE_EVENT(MY_EVENT, wxCommandEvent);
wxDEFINE_EVENT(MY_EVENT, wxCommandEvent);

// App
class App : public wxApp {
public:
  virtual bool OnInit() override;
  virtual int OnExit();
};

// MainFrame
class MainFrame : public wxFrame {
public:
  MainFrame() {}
  bool Create(const wxString& tilte);
};

// Panel1
class Panel1 : public wxPanel {
  DECLARE_EVENT_TABLE()

public:
  Panel1(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
    , parent_(parent) {
  }

private:
  void OnClick(wxCommandEvent& evt);

private:
  wxWindow* parent_;
};

BEGIN_EVENT_TABLE(Panel1, wxPanel)
EVT_BUTTON(wxID_OK, Panel1::OnClick)
END_EVENT_TABLE()

// Panel2
class Panel2 : public wxPanel {
  DECLARE_EVENT_TABLE()

public:
  Panel2(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id) {
  }

  void set_text_(wxStaticText* text) { text_ = text; }

private:
  void OnChange(wxCommandEvent& evt) {
    evt.GetEventType();
    text_->SetLabelText(evt.GetString());
  }

private:
  wxStaticText* text_;
};

BEGIN_EVENT_TABLE(Panel2, wxPanel)
EVT_COMMAND(ID_PANEL1, MY_EVENT, Panel2::OnChange)
END_EVENT_TABLE()

//--------------------------------------------

void Panel1::OnClick(wxCommandEvent& evt) {
  //wxStaticText* text = (wxStaticText*)parent_->FindWindowById(wxID_OPEN);
  //wxStaticText* text = (wxStaticText*)GetParent()->FindWindow(wxID_OPEN);
  //text->SetLabelText(wxT("123"));

  wxCommandEvent evt1(MY_EVENT, GetId());
  evt1.SetEventObject(this);
  evt1.SetString("456");
  //GetParent()->GetEventHandler()->AddPendingEvent(evt1);
  GetParent()->FindWindow(ID_PANEL2)->GetEventHandler()->AddPendingEvent(evt1);
}

bool MainFrame::Create(const wxString& tilte) {
  wxFrame::Create(NULL, wxID_ANY, tilte);
  wxSplitterWindow* splitter_window = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);

  Panel1* left_window = new Panel1(splitter_window, ID_PANEL1);
  left_window->SetBackgroundColour(*wxRED);
  left_window->SetCursor(wxCursor(wxCURSOR_RIGHT_ARROW));
  wxButton* button = new wxButton(left_window, wxID_OK, wxT("abc<-->123"));

  Panel2* right_window = new Panel2(splitter_window, ID_PANEL2);
  right_window->SetCursor(wxCursor(wxCURSOR_ARROW));
  wxStaticText* text = new wxStaticText(right_window, wxID_OPEN,wxT("abc"));
  right_window->set_text_(text);
  //splitter_window->SplitHorizontally(left_window, right_window);
  splitter_window->SplitVertically(left_window, right_window);
  return true;
}

IMPLEMENT_APP(App)

bool App::OnInit() {
  wxApp::OnInit();

  wxString title = wxT("   \tsadf\t  ");
  title.Trim(false);
  wxString title1 = wxT("   \tsadf\t  ");
  title1.Trim(true);

  MainFrame* main_frame = new MainFrame;
  main_frame->Create(wxT(""));
  main_frame->Show(true);
  return true;
}

int App::OnExit() {
  wxApp::OnExit();

  return 0;
}

#endif
