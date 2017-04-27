#if 1

#include "wx/wx.h"
#include "boost/lexical_cast.hpp"
#include <vector>
#include <string>

/// \brief Construct the date time corresponding to the GMT0 time zone, the
///        input string should has the format as "2010-12-10T16:31:00-08:00" or
///        "2010-12-10T16:31:00+08:00", the input date time string will be converted
///        to corresponding date time in the GMT0 time zone.
wxDateTime ConstructGMT0DateTime1(const std::string& strDateTime) {
  if (strDateTime.empty()) {
    wxDateTime emptyDateTime;
    return emptyDateTime;
  }

  bool lowerGMT0 = false;
  size_t indexTime = strDateTime.rfind("+");

  if (indexTime == std::string::npos) {
    indexTime = strDateTime.rfind("-");
    lowerGMT0 = true;
  }

  int nYear = 0, nDay = 0, nMonth = 0, nHour = 0, nMin = 0, nSeconds = 0, nTZHrs = 0, nTZMins = 0;

  if (lowerGMT0) {
    sscanf(strDateTime.c_str(), "%d-%d-%dT%d:%d:%d-%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMin, &nSeconds, &nTZHrs, &nTZMins);
    nTZHrs = -nTZHrs;
    nTZMins = -nTZMins;
  } else {
    sscanf(strDateTime.c_str(), "%d-%d-%dT%d:%d:%d+%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMin, &nSeconds, &nTZHrs, &nTZMins);
  }

  // Construct the GMT0 date time
  wxDateTime gmt0DateTime;
  gmt0DateTime.Set(nDay, wxDateTime::Month(nMonth - 1), nYear, nHour, nMin, nSeconds);
  gmt0DateTime.MakeFromTimezone(wxDateTime::TimeZone::Make(nTZHrs * 60 * 60), false);

  return gmt0DateTime;
}

/// \brief Construct the date time corresponding to the GMT0 time zone, the
///        input string should has the format as "2010-12-10T16:31:00-08:00" or
///        "2010-12-10T16:31:00+08:00", the input date time string will be converted
///        to corresponding date time in the GMT0 time zone.
wxDateTime ConstructGMT0DateTime2(const std::string& date_time_str) {
  const std::string kWestTimeZoneFormat = "--T::-:";
  const std::string kEastTimeZoneFormat = "--T::+:";

  std::string separators;
  std::vector<size_t> separator_positions;

  for (size_t i = 0; i < date_time_str.size(); ++i) {
    char ch = date_time_str[i];
    if (ch == '-' || ch == 'T' || ch == ':' || ch == '+') {
      separators.append(1, ch);
      separator_positions.push_back(i);
    }
  }

  if (separators != kEastTimeZoneFormat && separators != kWestTimeZoneFormat) {
    return wxInvalidDateTime;
  }

  std::string temp = date_time_str.substr(0, separator_positions[0]);
  int year = atoi(temp.c_str());
  temp = date_time_str.substr(separator_positions[0] + 1, separator_positions[1] - separator_positions[0] - 1);
  int month = atoi(temp.c_str());
  temp = date_time_str.substr(separator_positions[1] + 1, separator_positions[2] - separator_positions[1] - 1);
  int day = atoi(temp.c_str());
  temp = date_time_str.substr(separator_positions[2] + 1, separator_positions[3] - separator_positions[2] - 1);
  int hour = atoi(temp.c_str());
  temp = date_time_str.substr(separator_positions[3] + 1, separator_positions[4] - separator_positions[3] - 1);
  int minute = atoi(temp.c_str());
  temp = date_time_str.substr(separator_positions[4] + 1, separator_positions[5] - separator_positions[4] - 1);
  int second = atoi(temp.c_str());

  if (month > 12 || month < 1) {
    return wxInvalidDateTime;
  }

  if (day < 1 || day > wxDateTime::GetNumberOfDays((wxDateTime::Month)(month - 1), year)) {
    return wxInvalidDateTime;
  }

  temp = date_time_str.substr(separator_positions[5] + 1, separator_positions[6] - separator_positions[5] - 1);
  int time_zone_hour = atoi(temp.c_str());

  temp = date_time_str.substr(separator_positions[6] + 1);
  int time_zone_minute = atoi(temp.c_str());

  long time_zone_offset = time_zone_hour * 3600 + time_zone_minute * 60;
  if (separators == kWestTimeZoneFormat) {
    time_zone_offset = -time_zone_offset;
  }

  wxDateTime date_time;
  date_time.Set(day, wxDateTime::Month(month - 1), year, hour, minute, second);
  if (!date_time.IsValid()) {
    return wxInvalidDateTime;
  }

  date_time.MakeFromTimezone(wxDateTime::TimeZone::Make(time_zone_offset), false);

  return date_time;
}


wxDateTime ConstructGMT0DateTime3(const std::string& date_time_str) {
  wxString wx_date_time = wxString::FromAscii(date_time_str.data());

  bool is_lower_gmt0 = false;
  int date_pos = wx_date_time.Find(_T('+'), true);

  if (date_pos == wxNOT_FOUND) {
    date_pos = wx_date_time.Find(_T('-'), true);
    is_lower_gmt0 = true;
  }

  wxString wx_iso_date_time = wx_date_time.SubString(0, date_pos - 1);
  wxString wx_time_zone = wx_date_time.SubString(date_pos + 1, date_time_str.length() - 1);

  wxDateTime date_time;
  date_time.ParseISOCombined(wx_iso_date_time);

  if (!date_time.IsValid()) {
    return wxInvalidDateTime;
  }

  int time_zone_pos = wx_time_zone.Find(_T(':'));
  wxString time_zone_hour = wx_time_zone.SubString(0, time_zone_pos - 1);

  long zt_hour = 0;
  time_zone_hour.ToLong(&zt_hour);

  long time_zone_offset = zt_hour * 3600;
  if (is_lower_gmt0) {
    time_zone_offset = -time_zone_offset;
  }

  date_time.MakeFromTimezone(wxDateTime::TimeZone::Make(time_zone_offset), false);

  return date_time;
}

wxDateTime ConstructGMT0DateTime4(const std::string& date_time_str) {
  const std::string kWestTimeZoneFormat = "--T::-:";
  const std::string kEastTimeZoneFormat = "--T::+:";

  std::string separators;
  std::vector<int> separated_numbers;  // Sequence: year, month, day, hour, minute, second, time_zone_hour.
  int last_pos = -1;

  for (size_t i = 0; i < date_time_str.size(); ++i) {
    char ch = date_time_str[i];
    if (ch == '-' || ch == 'T' || ch == ':' || ch == '+') {
      std::string temp = date_time_str.substr(last_pos + 1, i - last_pos - 1);
      separated_numbers.push_back(atoi(temp.c_str()));
      separators.append(1, ch);
      last_pos = i;
    }
  }

  if (separators != kEastTimeZoneFormat && separators != kWestTimeZoneFormat) {
    return wxInvalidDateTime;
  }

  if (separated_numbers[1] > 12 || separated_numbers[1] < 1) {
    return wxInvalidDateTime;
  }

  if (separated_numbers[2] < 1 || separated_numbers[2] > wxDateTime::GetNumberOfDays((wxDateTime::Month)(separated_numbers[1] - 1), separated_numbers[0])) {
    return wxInvalidDateTime;
  }

  long time_zone_offset = separated_numbers[6] * 3600;
  if (separators == kWestTimeZoneFormat) {
    time_zone_offset = -time_zone_offset;
  }

  wxDateTime date_time;
  date_time.Set(separated_numbers[2], 
                wxDateTime::Month(separated_numbers[1] - 1),
                separated_numbers[0],
                separated_numbers[3],
                separated_numbers[4],
                separated_numbers[5]);
  if (!date_time.IsValid()) {
    return wxInvalidDateTime;
  }

  date_time.MakeFromTimezone(wxDateTime::TimeZone::Make(time_zone_offset), false);

  return date_time;
}

class MainFrame : public wxFrame {
  wxDECLARE_EVENT_TABLE();
public:
  MainFrame() {};
  bool Create(const wxString& title) {
    wxFrame::Create(NULL, wxID_ANY, title);
    wxButton* button = new wxButton(this, wxID_OK);
    wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    vsizer->Add(button, 1, wxEXPAND | wxALL, 50);
    SetSizer(vsizer);
    int a = atoi("");
    int b = atoi("a");
    int c = atoi("123");

    wxDateTime date;
    wxString tem;

    date = ConstructGMT0DateTime1("2011-2-28T16:00:00-8:00");
    wxString tem1 = date.FormatISOCombined();
    date = ConstructGMT0DateTime2("2011-2-28T16:00:00-8:00");
    wxString tem2 = date.FormatISOCombined();
    date = ConstructGMT0DateTime3("2011-2-28T16:00:00-8:00");
    wxString tem3 = date.FormatISOCombined();
    date = ConstructGMT0DateTime4("2011-2-28T16:00:00-8:00");
    wxString tem4 = date.FormatISOCombined();


    date = ConstructGMT0DateTime1("2011-2-28T16:00:00+8:00");
    wxString tem5 = date.FormatISOCombined();
    date = ConstructGMT0DateTime2("2011-2-28T16:00:00+8:00");
    wxString tem6 = date.FormatISOCombined();
    date = ConstructGMT0DateTime3("2011-2-28T16:00:00+8:00");
    wxString tem7 = date.FormatISOCombined();
    date = ConstructGMT0DateTime4("2011-2-28T16:00:00+8:00");
    wxString tem8 = date.FormatISOCombined();

    date = ConstructGMT0DateTime2("2010-12-32T16:00:00+3:00");
    date = ConstructGMT0DateTime2("2010-12-32T163:00");
    date = ConstructGMT0DateTime3("2010-12-32T16:00:00+3:00");
    date = ConstructGMT0DateTime3("2010-12-32T163:00");


    wxDateTime date_time;

     if (date_time.IsValid()) {
      date_time.Format(wxT("%H:%M:%S"));
    }

   //ConstructGMT0DateTime("--T::-:");


   //ConstructGMT0DateTime("2010-12-31T16:31:00-8:00");


   //ConstructGMT0DateTime("2010-12-31T1631:00-8:");

   //ConstructGMT0DateTime("2010-12-36T16:31:00+08:00");

    return true;
  }

  void OnOk(wxCommandEvent& evt) {
    wxMessageBox(wxT("Hello, world!"));
  }
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(wxID_OK, MainFrame::OnOk)
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
//int year = boost::lexical_cast<int>(date_time.substr(0, separator_positions[0]));
//int month = boost::lexical_cast<int>(date_time.substr(separator_positions[0] + 1, separator_positions[1] - separator_positions[0] - 1));
//int day = boost::lexical_cast<int>(date_time.substr(separator_positions[1] + 1, separator_positions[2] - separator_positions[1] - 1));
//int hour = boost::lexical_cast<int>(date_time.substr(separator_positions[2] + 1, separator_positions[3] - separator_positions[2] - 1));
//int minute = boost::lexical_cast<int>(date_time.substr(separator_positions[3] + 1, separator_positions[4] - separator_positions[3] - 1));
//int second = boost::lexical_cast<int>(date_time.substr(separator_positions[4] + 1, separator_positions[5] - separator_positions[4] - 1));

//int time_zone_hour = boost::lexical_cast<int>(date_time.substr(separator_positions[5] + 1, separator_positions[6] - separator_positions[5] - 1));
//int time_zone_minute = boost::lexical_cast<int>(date_time.substr(separator_positions[6] + 1));