#if 0

#include "wx/wx.h"
wxDECLARE_EVENT(myEVT_THREAD_UPDATE, wxThreadEvent);

class MyFrame : public wxFrame, public wxThreadHelper {
public:
  MyFrame(const wxString& title);

  // worker thread entry point
  wxThread::ExitCode Entry();

  // keyboard monitor
  void OnChar(wxKeyEvent& event);

  void OnButton(wxCommandEvent& evt);

  // display updater
  void OnTimer(wxTimerEvent& event);

  void OnUI(wxUpdateUIEvent& evt) {
  }

  void OnThreadUpdate(wxThreadEvent& evt);
private:

  // the counter
  unsigned int mCounter;

  // protect the counter from access by both threads at once
  wxCriticalSection mCS;

  // display update timer
  wxTimer * mTimer;

  DECLARE_EVENT_TABLE()
};

wxDEFINE_EVENT(myEVT_THREAD_UPDATE, wxThreadEvent);

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CHAR(MyFrame::OnChar)
EVT_BUTTON(wxID_OK, MyFrame::OnButton)
EVT_UPDATE_UI(wxID_OK, MyFrame::OnUI)
EVT_THREAD(10, MyFrame::OnThreadUpdate)
EVT_TIMER(-1, MyFrame::OnTimer)
END_EVENT_TABLE()
MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
, mCounter(0) {
  // set the frame icon
  SetIcon(wxICON(sample));
  wxButton* btn = new wxButton(this, wxID_OK, "aaaaaaaaaaaaaaaaaaa");

  CreateStatusBar(2);
  SetStatusText("Welcome to Asynchronous Counter!");

  // Create thread and start it going

  CreateThread();
  GetThread()->Run();

  // Create update timer and start it going

  mTimer = new wxTimer(this);
  mTimer->Start(500);
}

void MyFrame::OnButton(wxCommandEvent& evt) {
  wxMessageBox("");
}

wxThread::ExitCode MyFrame::Entry() {
  // loop, so long as we haven't been asked to quit
  while (!GetThread()->TestDestroy()) {
    {
      wxBusyCursor wait;
      // increment counter, to a maximum value
      wxCriticalSectionLocker lock(mCS);
      if (mCounter >= 0xFFFFFFFF)
        break;
      ++mCounter;
    }

    // Let other things happen for 1/10 second
    Sleep(1000);

    QueueEvent(new wxThreadEvent(wxEVT_THREAD, 10));
  }
  // Counter is finished, or we have been asked to stop
  return (wxThread::ExitCode)0;

}

void MyFrame::OnThreadUpdate(wxThreadEvent& evt) {
}

void MyFrame::OnChar(wxKeyEvent& event) {
  event.Skip();
  if (event.GetKeyCode() == (int) 'q')
    GetThread()->Delete();
}


void MyFrame::OnTimer(wxTimerEvent&) {
  unsigned int current_counter_value;
  {
    wxCriticalSectionLocker lock(mCS);
    current_counter_value = mCounter;
  }
  SetStatusText(wxString::Format("Counter = %d", current_counter_value));
}

class App : public wxApp {
public:
  virtual bool OnInit() override;
  virtual int OnExit() override;
};

wxDECLARE_APP(App);
wxIMPLEMENT_APP(App);

bool App::OnInit() {
  wxApp::OnInit();

  MyFrame* main_frame = new MyFrame("Thread");
  main_frame->Show(true);

  return true;
}

int App::OnExit() {
  wxApp::OnExit();

  return 0;
}
#endif
