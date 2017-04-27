#if 0

#include "wx/wx.h"
#include "wx/caret.h"

// TicketThread
class TicketThread : public wxThread {
public:
  TicketThread(const wxString& name, wxTextCtrl* text_ctrl)
    : name_(name)
    , text_ctrl_(text_ctrl) {
  }

  virtual void* Entry();

  wxString name() { return name_; }

private:
  static int counts_;

private:
  static wxCriticalSection critical_section_;

private:
  wxString name_;
  wxTextCtrl* text_ctrl_;
};

int TicketThread::counts_ = 50;
wxCriticalSection TicketThread::critical_section_;

void* TicketThread::Entry() {
  while (1) {
    wxCriticalSectionLocker locker(critical_section_);
    if (counts_ <= 0) {
      text_ctrl_->AppendText(wxT("Sell up!\n"));
      break;
    } else {
      text_ctrl_->AppendText(name_ + " : " + wxString::Format(wxT("%d"), counts_) + wxT("\n"));
      counts_--;
    }
    wxThread::Sleep(500);
  }
  return NULL;
}

// MainFrame
class MainFrame : public wxFrame {
  wxDECLARE_EVENT_TABLE();
public:
  MainFrame()
    : text_ctrl1_(NULL)
    , text_ctrl2_(NULL)
    , text_ctrl3_(NULL) {
  }

  bool Create(const wxString& title) {
    wxFrame::Create(NULL, wxID_ANY, title);

    CreateControls();

    SellTicket();

    return true;
  }

private:
  void SellTicket();

  TicketThread* CreateThread(const wxString& name, wxTextCtrl* text_ctrl);

  void CreateControls();

private:
  wxTextCtrl* text_ctrl1_;
  wxTextCtrl* text_ctrl2_;
  wxTextCtrl* text_ctrl3_;
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
wxEND_EVENT_TABLE()

// App
class App : public wxApp {
public:
  virtual bool OnInit() override;
  virtual int OnExit() override;
};

wxDECLARE_APP(App);
wxIMPLEMENT_APP(App);

//---------------------------------------------------------

TicketThread* MainFrame::CreateThread(const wxString& name, wxTextCtrl* text_ctrl) {
  TicketThread* ticket_thread = new TicketThread(name, text_ctrl);
  if (ticket_thread->Create() != wxTHREAD_NO_ERROR) {
    wxLogError(wxT("Can't create thread!"));
  }
  return ticket_thread;
}


void MainFrame::CreateControls() {
  text_ctrl1_ = new wxTextCtrl(this,
                               wxID_ANY,
                               wxEmptyString,
                               wxDefaultPosition,
                               wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

  text_ctrl2_ = new wxTextCtrl(this,
                               wxID_ANY,
                               wxEmptyString,
                               wxDefaultPosition,
                               wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

  text_ctrl3_ = new wxTextCtrl(this,
                               wxID_ANY,
                               wxEmptyString,
                               wxDefaultPosition,
                               wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

  wxBoxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);
  hsizer->Add(text_ctrl1_, 1, wxEXPAND);
  hsizer->AddSpacer(20);
  hsizer->Add(text_ctrl2_, 1, wxEXPAND);
  hsizer->AddSpacer(20);
  hsizer->Add(text_ctrl3_, 1, wxEXPAND);

  SetSizer(hsizer);
}

void MainFrame::SellTicket() {
  TicketThread* window1 = CreateThread(wxT("Window1"), text_ctrl1_);
  TicketThread* window2 = CreateThread(wxT("Window2"), text_ctrl2_);
  TicketThread* window3 = CreateThread(wxT("Window3"), text_ctrl3_);

  window1->Run();
  window2->Run();
  window3->Run();
}


bool App::OnInit() {
  wxApp::OnInit();

  MainFrame* main_frame = new MainFrame();
  main_frame->Create(wxT("Thread"));
  main_frame->Show(true);

  return true;
}

int App::OnExit() {
  wxApp::OnExit();

  return 0;
}

#endif
