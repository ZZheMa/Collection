#ifndef CSI_STRING_H_
#define CSI_STRING_H_
#pragma once

#include <iostream>

class CsiString {
public:
  CsiString();
  CsiString(const char* c_str);
  CsiString(size_t n, char ch);
  CsiString(const CsiString& csi_str);
  CsiString(const CsiString& csi_str, size_t pos, size_t n = NPOS);
  ~CsiString();

  size_t len() const { return len_; }
  size_t capacity() const { return capacity_; }
  const char* c_str() const { return buf_; }

  bool IsEmpty() const;
  void Clear();
  size_t Size() const;
  void Resize(size_t n);
  void Resize(size_t n, char ch);
  void Reserve(size_t n = 0);
  const char& At(size_t pos) const;
  char& At(size_t pos);
  CsiString& Append(const CsiString& csi_str);
  CsiString& Append(const char* c_str);
  CsiString& Assign(const CsiString& csi_str);
  CsiString& Assign(const char* c_str);
  CsiString& Insert(size_t pos, const CsiString& csi_str);
  CsiString& Insert(size_t pos, const char* c_str);
  CsiString& Erase(size_t pos = 0, size_t n = NPOS);
  int Compare(const CsiString& csi_str) const;
  int Compare(const char* c_str) const;
  CsiString SubStr(size_t pos = 0, size_t n = NPOS) const;
  bool StartWith(const char* c_str) const;
  bool EndWith(const char* c_str) const;
  size_t Find(const char* c_str, size_t pos = 0) const;
  size_t Find(const CsiString& csi_str, size_t pos = 0) const;
  CsiString& Replace(size_t pos, size_t n, const char* c_str);
  CsiString& Replace(const char* src_str, const char* target_str);

  friend std::istream& operator>>(std::istream& is, CsiString& csi_str);
  friend std::ostream& operator<<(std::ostream& os, const CsiString& csi_str);
  friend CsiString operator+(const CsiString& left_csi_str, const CsiString& right_csi_str);
  friend CsiString operator+(const CsiString& left_csi_str, const char* right_c_str);
  friend CsiString operator+(const char* left_c_str, const CsiString& right_csi_str);
  friend bool operator==(const CsiString& left_csi_str, const CsiString& right_csi_str);
  friend bool operator!=(const CsiString& left_csi_str, const CsiString& right_csi_str);
  friend bool operator<(const CsiString& left_csi_str, const CsiString& right_csi_str);
  friend bool operator>(const CsiString& left_csi_str, const CsiString& right_csi_str);
  friend bool operator>=(const CsiString& left_csi_str, const CsiString& right_csi_str);
  friend bool operator<=(const CsiString& left_csi_str, const CsiString& right_csi_str);
  CsiString& operator=(const CsiString& csi_str);
  CsiString& operator=(const char* c_str);
  CsiString& operator=(char ch);
  CsiString& operator+=(const CsiString& csi_str);
  CsiString& operator+=(const char* c_str);
  const char& operator[](size_t pos) const;
  char& operator[](size_t pos);

public:
  static const size_t NPOS;

private:
  char* buf_;
  size_t capacity_;
  size_t len_;
};

#endif  // CSI_STRING_H_
