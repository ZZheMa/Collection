#include "07static_text.h"
#include "wx/dcbuffer.h"

BEGIN_EVENT_TABLE(StaticText, wxControl)
EVT_PAINT(StaticText::OnPaint)
EVT_LEFT_DOWN(StaticText::OnMouseLeftDown)
EVT_LEFT_UP(StaticText::OnMouseLeftUp)
END_EVENT_TABLE()

StaticText::StaticText() {
}

StaticText::~StaticText() {
}

bool StaticText::Create(wxWindow* patent, int id, const wxString& text) {
  if (!wxControl::Create(patent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)) {
    return false;
  }

  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  SetLabel(text);

  text_ = text;

  return true;
}

void StaticText::OnPaint(wxPaintEvent& evt) {
  wxAutoBufferedPaintDC dc(this);
  dc.Clear();
  dc.DrawText(text_, wxPoint(0, 0));
}

void StaticText::OnMouseLeftDown(wxMouseEvent& evt) {
  if (!HasCapture()) {
    CaptureMouse();
  }
}

void StaticText::OnMouseLeftUp(wxMouseEvent& evt) {
  if (HasCapture()) {
    ReleaseMouse();
  }

  //wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
  //evt.SetEventObject(this);
  //GetParent()->GetEventHandler()->AddPendingEvent(evt);
}
