#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>
#include <locale>
#include <codecvt>
#include <fstream>

std::string ConvertUtf16ToUtf8(const std::wstring& utf16_string) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return converter.to_bytes(utf16_string);
}

std::wstring ConvertUtf8ToUtf16(const std::string& utf8_string) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return converter.from_bytes(utf8_string);
}

int main() {
  std::string a1 = "一二三";

  std::wstring a2 = L"一二三";
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  std::string a3 = converter.to_bytes(a2);

  std::wstring a4 = ConvertUtf8ToUtf16(a3);

  std::ofstream ofs("C:\\Users\\Admin\\Desktop\\New folder\\a.txt");
  ofs << a3;
  return 0;
}
