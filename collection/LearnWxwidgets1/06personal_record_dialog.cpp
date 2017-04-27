#include "06personal_record_dialog.h"

#include "wx/dialog.h"
#include "wx/stattext.h"
#include "wx/button.h"
#include "wx/spinctrl.h"
#include "wx/choice.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/checkbox.h"
#include "wx/statline.h"

#define DESCR _("Please enter your name, age and sex, and specify whether you wish to vote in a general election.")
#define FEMALE _("Female")
#define MALE _("Male")
#define NAME_DESCR _("Enter your full name")

BEGIN_EVENT_TABLE(PersonalRecordDialog, wxDialog)
EVT_BUTTON(ID_RESET_BUTTON, PersonalRecordDialog::OnResetButtonClick)
EVT_BUTTON(ID_OK_BUTTON, PersonalRecordDialog::OnOkButtonClick)
EVT_BUTTON(ID_CANCEL_BUTTON, PersonalRecordDialog::OnCancelButtonClick)
EVT_BUTTON(ID_HELP_BUTTON, PersonalRecordDialog::OnHelpButtonClick)
EVT_UPDATE_UI(ID_VOTE_CHECK_BOX, PersonalRecordDialog::OnVoteCheckBoxUpdateUI)
END_EVENT_TABLE()

PersonalRecordDialog::PersonalRecordDialog(Person* person)
    : person_(person) {
  Init();
}

PersonalRecordDialog::~PersonalRecordDialog() {
}

bool PersonalRecordDialog::Create(wxWindow* parent, int id, const wxString& title) {
  if (!wxDialog::Create(parent, id, title)) {
    return false;
  }

  SetBackgroundColour(*wxWHITE);

  CreateControls();
  Fit();

  return true;
}

void PersonalRecordDialog::CreateControls() {
  wxSizer* top_vsizer = new wxBoxSizer(wxVERTICAL);

  descr_label_ = new wxStaticText(this, wxID_ANY, DESCR);
  top_vsizer->Add(descr_label_);
  top_vsizer->AddSpacer(10);

  name_label_ = new wxStaticText(this, wxID_ANY, _("Name:"));
  top_vsizer->Add(name_label_);
  top_vsizer->AddSpacer(10);

  name_text_ctrl_ = new wxTextCtrl(this, wxID_ANY);
  name_text_ctrl_->SetToolTip(NAME_DESCR);
  top_vsizer->Add(name_text_ctrl_);
  top_vsizer->AddSpacer(10);

  age_label_ = new wxStaticText(this, wxID_ANY, _("Age:"));
  top_vsizer->Add(age_label_);
  top_vsizer->AddSpacer(10);

  age_spin_ctrl_ = new wxSpinCtrl(this, wxID_ANY);
  top_vsizer->Add(age_spin_ctrl_);
  top_vsizer->AddSpacer(10);

  sex_label_ = new wxStaticText(this, wxID_ANY, _("Sex:"));
  top_vsizer->Add(sex_label_);
  top_vsizer->AddSpacer(10);

  sex_choice_ = new wxChoice(this, wxID_ANY);
  sex_choice_->Append(FEMALE);
  sex_choice_->Append(_("Male"));
  top_vsizer->Add(sex_choice_);
  top_vsizer->AddSpacer(10);

  vote_check_box_ = new wxCheckBox(this, ID_VOTE_CHECK_BOX, _("Vote"));
  top_vsizer->Add(vote_check_box_);
  top_vsizer->AddSpacer(10);


  separation_line_ = new wxStaticLine(this, wxID_ANY);
  separation_line_->SetBackgroundColour(*wxBLACK);
  top_vsizer->Add(separation_line_, 1, wxEXPAND);
  top_vsizer->AddSpacer(10);

  wxSizer* button_hsizer = new wxBoxSizer(wxHORIZONTAL);

  reset_button_ = new wxButton(this, ID_RESET_BUTTON, _("Reset"));
  ok_button_ = new wxButton(this, ID_OK_BUTTON, _("OK"));
  cancel_button_ = new wxButton(this, ID_CANCEL_BUTTON, _("Cancel"));
  help_button_ = new wxButton(this, ID_HELP_BUTTON, _("Help"));

  button_hsizer->Add(reset_button_);
  button_hsizer->AddSpacer(10);
  button_hsizer->Add(ok_button_);
  button_hsizer->AddSpacer(10);
  button_hsizer->Add(cancel_button_);
  button_hsizer->AddSpacer(10);
  button_hsizer->Add(help_button_);
  button_hsizer->AddSpacer(10);

  top_vsizer->Add(button_hsizer);
  top_vsizer->AddSpacer(40);

  SetSizer(top_vsizer);
}

void PersonalRecordDialog::Init() {
  separation_line_ = NULL;

  descr_label_ = NULL;
  name_label_ = NULL;
  age_label_ = NULL;
  sex_label_ = NULL;

  age_spin_ctrl_ = NULL;
  sex_choice_ = NULL;
  vote_check_box_ = NULL;
  name_text_ctrl_ = NULL;

  reset_button_ = NULL;
  ok_button_ = NULL;
  cancel_button_ = NULL;
  help_button_ = NULL;
}

bool PersonalRecordDialog::TransferDataFromWindow() {
  person_->age = age_spin_ctrl_->GetValue();
  wxString name = name_text_ctrl_->GetValue();
  person_->name = name.Trim(false).Trim();
  person_->is_vote = vote_check_box_->GetValue();
  person_->sex = sex_choice_->GetStringSelection();

  return true;
}

bool PersonalRecordDialog::TransferDataToWindow() {
  if ((person_->sex).IsSameAs(FEMALE, false)) {
    sex_choice_->SetStringSelection(FEMALE);
  } else {
    sex_choice_->SetStringSelection(MALE);
  }

  age_spin_ctrl_->SetValue(person_->age);
  name_text_ctrl_->ChangeValue(person_->name);
  name_text_ctrl_->SetInsertionPointEnd();
  vote_check_box_->SetValue(person_->is_vote);

  return true;
}

void PersonalRecordDialog::OnVoteCheckBoxUpdateUI(wxUpdateUIEvent& evt) {
  int age = age_spin_ctrl_->GetValue();
  if (age < 18) {
    evt.Check(false);
    evt.Enable(false);
  } else {
    evt.Enable(true);
  }
}

void PersonalRecordDialog::OnOkButtonClick(wxCommandEvent& evt) {
  TransferDataFromWindow();
  EndModal(wxOK);
}

void PersonalRecordDialog::OnCancelButtonClick(wxCommandEvent& evt) {
  EndModal(wxCANCEL);
}

void PersonalRecordDialog::OnResetButtonClick(wxCommandEvent& evt) {
  TransferDataToWindow();
}

void PersonalRecordDialog::OnHelpButtonClick(wxCommandEvent& evt) {
}