#if 0

#include "wx/wx.h"

// 2.自定义事件类

enum {
  ID_LEFT_PANEL = 0,
  ID_RIGHT_PANEL,
};

// App
class App : public wxApp {
public:
  bool OnInit() override;
  int OnExit() override;
};

IMPLEMENT_APP(App);

// MyPlotEvent

class MyPlotEvent : public wxCommandEvent {
  DECLARE_DYNAMIC_CLASS_NO_ASSIGN(MyPlotEvent)

public:
  MyPlotEvent(wxEventType evt_type = wxEVT_NULL, int winid = 0)
    : wxCommandEvent(evt_type, winid) {
  }

  MyPlotEvent(const MyPlotEvent& rhs)
    : wxCommandEvent(rhs)
    , pos_(rhs.pos_) {
  }

  virtual wxEvent* Clone() const {
    return new MyPlotEvent(*this);
  }

  void set_pos(const wxPoint& pos) { pos_ = pos; }
  wxPoint pos() const { return pos_; }

private:
  wxPoint pos_;
};

typedef void (wxEvtHandler::*MyPlotEventFunction)(MyPlotEvent&);

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_MYPLOT_LCLICK, -1)
END_DECLARE_EVENT_TYPES()

#define MyPlotEventHandler(func)\
  (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(MyPlotEventFunction, &func)

#define EVT_MYPLOT_LCLICK(id, func)\
  DECLARE_EVENT_TABLE_ENTRY(wxEVT_MYPLOT_LCLICK, id, -1, MyPlotEventHandler(func), NULL),

IMPLEMENT_DYNAMIC_CLASS(MyPlotEvent, wxCommandEvent)
DEFINE_EVENT_TYPE(wxEVT_MYPLOT_LCLICK)

// LeftPanel
class LeftPanel : public wxPanel {
  DECLARE_EVENT_TABLE()
public:
  LeftPanel(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id) {
    SetBackgroundColour(*wxLIGHT_GREY);
  }

private:
  void OnLeftClick(wxMouseEvent& evt) {
    MyPlotEvent my_plot_evt(wxEVT_MYPLOT_LCLICK, GetId());
    my_plot_evt.set_pos(evt.GetPosition());
    my_plot_evt.SetEventObject(this);
    GetParent()->FindWindow(ID_RIGHT_PANEL)->GetEventHandler()->AddPendingEvent(my_plot_evt);
  }
};

BEGIN_EVENT_TABLE(LeftPanel, wxPanel)
EVT_LEFT_DOWN(LeftPanel::OnLeftClick)
END_EVENT_TABLE()

// RightPanel
class RightPanel : public wxPanel {
  DECLARE_EVENT_TABLE()
public:
  RightPanel(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id) {
    SetBackgroundColour(*wxWHITE);
  }

private:
  void OnMyPlot(MyPlotEvent& evt) {
    wxClientDC dc(this);
    dc.DrawCircle(evt.pos(), 10);
  }
};

BEGIN_EVENT_TABLE(RightPanel, wxPanel)
EVT_MYPLOT_LCLICK(ID_LEFT_PANEL, RightPanel::OnMyPlot)
END_EVENT_TABLE()

//----------------------------------

bool App::OnInit() {
  wxApp::OnInit();
  wxFrame* main_frame = new wxFrame(NULL, wxID_ANY, wxT("title"));
  LeftPanel* left_panel = new LeftPanel(main_frame, ID_LEFT_PANEL);
  RightPanel* right_panel = new RightPanel(main_frame, ID_RIGHT_PANEL);
  wxBoxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);
  hsizer->Add(left_panel, 1, wxEXPAND);
  hsizer->Add(right_panel, 1, wxEXPAND);
  main_frame->SetSizer(hsizer);
  main_frame->Show(true);

  return true;
}

int App::OnExit() {
  wxApp::OnExit();
  return 0;
}

#endif
