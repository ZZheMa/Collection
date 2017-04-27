#pragma once

#include "wx/dialog.h"
#include "06person.h"

class wxStaticText;
class wxStaticLine;
class wxSpinCtrl;
class wxChoice;
class wxCheckBox;
class wxButton;
class wxTextCtrl;

enum ResourceId {
  ID_OK_BUTTON,
  ID_CANCEL_BUTTON,
  ID_RESET_BUTTON,
  ID_HELP_BUTTON,

  ID_NAME_TEXT_CTRL,
  ID_AGE_SPIN_CTRL,
  ID_SEX_CHOICE,
  ID_VOTE_CHECK_BOX
};

class PersonalRecordDialog : public wxDialog {
  DECLARE_EVENT_TABLE()
public:
  PersonalRecordDialog(Person* person);

  ~PersonalRecordDialog();

  bool Create(wxWindow* parent, int id, const wxString& title);

  void CreateControls();

private:
  void Init();

  void OnOkButtonClick(wxCommandEvent& evt);
  void OnCancelButtonClick(wxCommandEvent& evt);
  void OnResetButtonClick(wxCommandEvent& evt);
  void OnHelpButtonClick(wxCommandEvent& evt);
  void OnVoteCheckBoxUpdateUI(wxUpdateUIEvent& evt);

  virtual bool TransferDataToWindow() override;
  virtual bool TransferDataFromWindow() override;

private:
  Person* person_;

  wxStaticText* descr_label_;
  wxStaticText* name_label_;
  wxStaticText* age_label_;
  wxStaticText* sex_label_;

  wxStaticLine* separation_line_;

  wxTextCtrl* name_text_ctrl_;
  wxSpinCtrl* age_spin_ctrl_;
  wxChoice* sex_choice_;
  wxCheckBox* vote_check_box_;

  wxButton* reset_button_;
  wxButton* ok_button_;
  wxButton* cancel_button_;
  wxButton* help_button_;
};
