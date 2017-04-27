#pragma once

#include "wx/control.h"

class StaticText : public wxControl {
  DECLARE_EVENT_TABLE()

public:
  StaticText();
  ~StaticText();

  bool Create(wxWindow* patent, int id, const wxString& text);

  void set_padding(const wxSize& padding) { padding_ = padding; }

private:
  void OnPaint(wxPaintEvent& evt);
  void OnMouseLeftDown(wxMouseEvent& evt);
  void OnMouseLeftUp(wxMouseEvent& evt);

private:
  wxString text_;
  wxSize padding_;
};
