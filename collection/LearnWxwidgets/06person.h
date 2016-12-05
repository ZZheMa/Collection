#pragma once

#include "wx/string.h"

struct Person {
  wxString name;
  wxString sex;
  int age;
  bool is_vote;

  Person()
    : sex(wxT("female"))
    , age(0)
    , is_vote(false) {
  }
};
