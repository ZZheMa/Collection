#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

const char* kPath = "C:\\Users\\Admin\\Desktop\\EditorConfig.xml";

int main2() {
  ifstream ifs(kPath, ios::in);
  if (!ifs.is_open() || !ifs.good()) {
    return 1;
  }
  string tem;
  char buf[256] = "";
  while (!ifs.eof()) {
    ifs.read(buf, 256);
    //ifs.getline(buf, 11);
    tem.append(buf, 0, static_cast<size_t>(ifs.gcount()));
  }
  //ofstream ofs(kPath, ios::out);
  //string s = "abc\na\rsd\r\ndg\n\r";
  //ofs << s.c_str();
  //ofs.close();

  return 0;
}

