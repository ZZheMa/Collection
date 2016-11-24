#include "csi_string.h"
#include <cassert>

const size_t kDefaultBufSize = 16;

const size_t CsiString::NPOS = -1;

CsiString::CsiString() {
  capacity_ = kDefaultBufSize;
  buf_ = new char[capacity_ + 1];
  buf_[0] = '\0';
  len_ = 0;
}

CsiString::CsiString(size_t n, char ch) {
  capacity_ = n + kDefaultBufSize;
  buf_ = new char[capacity_ + 1];
  len_ = n;
  for (size_t i = 0; i < n; ++i) {
    buf_[i] = ch;
  }
  buf_[len_] = '\0';
}

CsiString::CsiString(const char* c_str) {
  size_t c_str_size = strlen(c_str);
  capacity_ = c_str_size + kDefaultBufSize;
  buf_ = new char[capacity_ + 1];
  strcpy(buf_, c_str);
  len_ = c_str_size;
}

CsiString::CsiString(const CsiString& csi_str) {
  buf_ = new char[csi_str.capacity_ + 1];
  strcpy(buf_, csi_str.buf_);
  capacity_ = csi_str.capacity_;
  len_ = csi_str.len_;
}

CsiString::CsiString(const CsiString& csi_str, size_t pos, size_t n) {
  if (pos > len_) {
    throw std::out_of_range("invalid string position");
  }
  if (pos + n > len_) {
    n = csi_str.len_ - pos;
  }
  size_t size = n + kDefaultBufSize;
  buf_ = new char[size + 1];
  len_ = n;
  capacity_ = size;
  for (size_t i = 0; i < n; ++i) {
    buf_[i] = csi_str.buf_[pos + i];
  }
  buf_[len_] = '\0';
}

CsiString::~CsiString() {
  if (buf_ != NULL) {
    delete[] buf_;
    capacity_ = 0;
    len_ = 0;
  }
}

CsiString& CsiString::operator=(const CsiString& csi_str) {
  return operator=(csi_str.buf_);
}

CsiString& CsiString::operator=(const char* c_str) {
  size_t size = strlen(c_str);
  if (size <= capacity_) {
    strcpy(buf_, c_str);
    len_ = size;
  } else {
    char* temp = buf_;
    size += kDefaultBufSize;
    buf_ = new char[size + 1];
    strcpy(buf_, c_str);
    capacity_ = size;
    len_ = size - kDefaultBufSize;
    delete[] temp;
  }
  return *this;
}

CsiString& CsiString::operator=(char ch) {
    buf_[0] = ch;
    buf_[1] = '\0';
    len_ = 1;
  return *this;
}

CsiString& CsiString::operator+=(const CsiString& csi_str) {
  return Append(csi_str);
}

CsiString& CsiString::operator+=(const char* c_str) {
  return Append(c_str);
}

const char& CsiString::operator[](size_t pos) const {
  assert(pos < len_);
  return buf_[pos];
}

char& CsiString::operator[](size_t pos) {
  assert(pos < len_);
  return buf_[pos];
}

std::ostream& operator<<(std::ostream& os, const CsiString& csi_str) {
  os << csi_str.buf_;
  return os;
}

std::istream& operator>>(std::istream& is, CsiString& csi_str) {
  const size_t kMaxTempSize = 10000;
  char* temp = new char[kMaxTempSize];
  is >> temp;
  size_t size = strlen(temp);
  if (size <= csi_str.capacity_) {
    strcpy(csi_str.buf_, temp);
    csi_str.len_ = size;
  } else {
    char* temp2 = csi_str.buf_;
    size += kDefaultBufSize;
    csi_str.buf_ = new char[size + 1];
    strcpy(csi_str.buf_, temp);
    csi_str.capacity_ = size;
    csi_str.len_ = size - kDefaultBufSize;
    delete[] temp2;
  }
  delete[] temp;
  return is;
}

CsiString operator+(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return CsiString(left_csi_str).Append(right_csi_str);
}

CsiString operator+(const CsiString& left_csi_str, const char* right_c_str) {
  return CsiString(left_csi_str).Append(right_c_str);
}

CsiString operator+(const char* left_c_str, const CsiString& right_csi_str) {
  return CsiString(left_c_str).Append(right_csi_str);
}

bool operator==(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return strcmp(left_csi_str.buf_, right_csi_str.buf_) == 0;
}

bool operator!=(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return strcmp(left_csi_str.buf_, right_csi_str.buf_) != 0;
}

bool operator<(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return strcmp(left_csi_str.buf_, right_csi_str.buf_) == -1;
}

bool operator>(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return strcmp(left_csi_str.buf_, right_csi_str.buf_) == 1;
}

bool operator>=(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return strcmp(left_csi_str.buf_, right_csi_str.buf_) >= 0;
}

bool operator<=(const CsiString& left_csi_str, const CsiString& right_csi_str) {
  return strcmp(left_csi_str.buf_, right_csi_str.buf_) <= 0;
}

bool CsiString::IsEmpty() const{
  return len_ == 0;
}

void CsiString::Clear() {
  buf_[0] = '\0';
  len_ = 0;
}

size_t CsiString::Size() const{
  return len_;
}

void CsiString::Resize(size_t n) {
  if (n <= len_) {
    buf_[n] = '\0';
    len_ = n;
  } else {
    if (n <= capacity_) {
      for (size_t i = len_; i < n; i++) {
        buf_[i] = ' ';
      }
      buf_[n] = '\0';
      len_ = n;
    } else {
      size_t size = n + kDefaultBufSize;
      char* temp = buf_;
      buf_ = new char[size + 1];
      strcpy(buf_, temp);
      for (size_t i = len_; i < n; i++) {
        buf_[i] = ' ';
      }
      delete[] temp;
      buf_[n] = '\0';
      len_ = n;
      capacity_ = size;
    }
  }
}

void CsiString::Resize(size_t n, char ch) {
  if (n > len_) {
    if (n <= capacity_) {
      for (size_t i = len_; i < n; i++) {
        buf_[i] = ch;
      }
      buf_[n] = '\0';
      len_ = n;
    } else {
      size_t size = n + kDefaultBufSize;
      char* temp = buf_;
      buf_ = new char[size + 1];
      strcpy(buf_, temp);
      for (size_t i = len_; i < n; i++) {
        buf_[i] = ch;
      }
      buf_[n] = '\0';
      len_ = n;
      capacity_ = size;
      delete[] temp;
    }
  }
}

void CsiString::Reserve(size_t n) {
  if (n > capacity_) {
    size_t size = n + kDefaultBufSize;
    char* temp = buf_;
    buf_ = new char[size + 1];
    strcpy(buf_, temp);
    capacity_ = size;
    delete[] temp;
  } else {
    if (n > len_) {
      char* temp = buf_;
      buf_ = new char[n];
      strcpy(buf_, temp);
      capacity_ = n;
      delete[] temp;
    }
  }
}

const char& CsiString::At(size_t pos) const {
  if (pos < len_) {
    return buf_[pos];
  } else {
    throw std::out_of_range("invalid string position");
  }
}

char& CsiString::At(size_t pos) {
  if (pos < len_) {
    return buf_[pos];
  } else {
    throw std::out_of_range("invalid string position");
  }
}

CsiString& CsiString::Append(const CsiString& csi_str) {
  return Append(csi_str.buf_);
}

CsiString& CsiString::Append(const char* c_str) {
  size_t size = len_ + strlen(c_str);
  if (size <= capacity_) {
    strcat(buf_, c_str);
    len_ = size;
  } else {
    char* temp = buf_;
    buf_ = new char[size + kDefaultBufSize + 1];
    strcpy(buf_, temp);
    strcat(buf_, c_str);
    capacity_ = size + kDefaultBufSize;
    len_ = size;
    delete[] temp;
  }
  return *this;
}

CsiString& CsiString::Assign(const CsiString& csi_str) {
  return operator=(csi_str);
}

CsiString& CsiString::Assign(const char* c_str) {
  return operator=(c_str);
}

CsiString& CsiString::Insert(size_t pos, const CsiString& csi_str) {
  return Insert(pos, csi_str.buf_);
}

CsiString& CsiString::Insert(size_t pos, const char* c_str) {
  if (pos > len_) {
    throw std::out_of_range("invalid string position");
  }
  size_t c_str_size = strlen(c_str);
  size_t size = c_str_size + len_;
  if (size <= capacity_) {
    for (size_t i = size - 1; i >= pos + c_str_size; --i) {
      buf_[i] = buf_[i - c_str_size];
    }
    for (size_t i = 0; i < c_str_size; ++i) {
      buf_[i + pos] = c_str[i];
    }
    buf_[size] = '\0';
    len_ = size;
  } else {
    char* temp = buf_;
    buf_ = new char[size + kDefaultBufSize + 1];
    for (size_t i = 0; i < pos; ++i) {
      buf_[i] = temp[i];
    }
    for (size_t i = pos; i < pos + c_str_size; ++i) {
      buf_[i] = c_str[i - pos];
    }
    for (size_t i = pos + c_str_size; i < size; ++i) {
      buf_[i] = temp[i - c_str_size];
    }
    buf_[size] = '\0';
    len_ = size;
    capacity_ = size + kDefaultBufSize;
    delete[] temp;
  }
  return *this;
}

CsiString& CsiString::Erase(size_t pos, size_t n) {
  if (pos > len_) {
    throw std::out_of_range("invalid string position");
  }
  if (pos + n > len_) {
    buf_[pos] = '\0';
  } else {
    for (size_t i = 0; i < len_ - pos - n; ++i) {
      buf_[pos + i] = buf_[pos + i + n];
    }
    buf_[len_ - n] = '\0';
    len_ = len_ - n;
  }
  return *this;
}

int CsiString::Compare(const char* c_str) const {
  return strcmp(buf_, c_str);
}

int CsiString::Compare(const CsiString& csi_str) const {
  return Compare(csi_str.buf_);
}

CsiString CsiString::SubStr(size_t pos, size_t n) const {
  return CsiString(*this, pos, n);
}

bool CsiString::StartWith(const char* c_str) const {
  if (c_str == NULL) {
    return false;
  }
  return strncmp(c_str, buf_, strlen(c_str)) == 0;
}

bool CsiString::EndWith(const char* c_str) const {
  if (c_str == NULL) {
    return false;
  }
  size_t end_size = strlen(c_str);
  if (len_ < end_size) {
    return false;
  }
  return strcmp(buf_ + len_ - end_size, c_str) == 0;
}

size_t CsiString::Find(const char* c_str, size_t pos) const {
  if (pos > len_) {
    return NPOS;
  }
  size_t sub_str_size = strlen(c_str);
  for (size_t i = pos; sub_str_size + i <= len_; ++i) {
    if (strncmp(buf_ + i, c_str, sub_str_size) == 0) {
      return i;
    }
  }
  return NPOS;
}
size_t CsiString::Find(const CsiString& csi_str, size_t pos) const {
  return Find(csi_str.buf_, pos);
}

CsiString& CsiString::Replace(size_t pos, size_t n, const char* dst_str) {
  if (pos > len_) {
    throw std::out_of_range("invalid string position");
  }
  if (pos + n > len_) {
    n = len_ - pos;
  }
  size_t dst_str_size = strlen(dst_str);
  size_t size = dst_str_size + len_ - n;
  if (size > capacity_) {
    char* temp = buf_;
    buf_ = new char[size + kDefaultBufSize + 1];
    strcpy(buf_, temp);
    delete[] temp;
    capacity_ = size;
  }
  char* temp = new char[len_ - n + 1];
  strcpy(temp, buf_ + pos + n);
  strcpy(buf_ + pos, dst_str);
  strcpy(buf_ + pos + dst_str_size, temp);
  len_ = len_ + dst_str_size - n;
  delete[] temp;
  return *this;

}

CsiString& CsiString::Replace(const char* src_str, const char* dst_str) {
  size_t pos = Find(src_str);
  if (pos == NPOS) {
    return *this;
  }
  size_t n = strlen(src_str);
  return Replace(pos, n, dst_str);
}
