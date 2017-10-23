#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

#include "tinyxml/tinyxml.h"

namespace tinyxml_demo {

static const char* kFileName = "students.xml";

// 链接问题：另外从error LNK2001: 无法解析的外部符号 "private: static struct TiXmlString::Rep TiXmlString::nullrep_" 
// (?nullrep_@TiXmlString@@0URep@1@A)，这个错误出现的原因是因为你使用的是非stl版本的string类型。
// 如果你没有在工程中定义TIXML_USE_STL，那么你一定要加载tinystr.cpp；否则你可以不用添加tinystr.cpp到工程中。

struct Student {
  int id;
  std::string name;
  int age;

  Student(int id_, const std::string& name_, int age_)
      : id(id_)
      , name(name_)
      , age(age_) {
  }

  void Print() const {
    std::cout << "Id: " << id << ", Name: " << name << ", Age: " << age << std::endl;
  }
};

}  // tinyxml_demo

using namespace std;
using namespace tinyxml_demo;

//<?xml version="1.0" encoding="utf-8" ?>
//<Students>
//  <Student id = "1">
//    <Name>MaZhe</Name>
//    <Age>18</Age>
//  </Student>
//  <Student id = "2">
//    <Name>MaZhe</Name>
//    <Age>18</Age>
//  </Student>
//  <Student id = "3">
//    <Name>MaZhe</Name>
//    <Age>18</Age>
//  </Student>
//</Students>

static void WriteData() {
  // Prepare data.
  std::list<Student> students;
  students.push_back(Student(1, "MaZhe", 18));
  students.push_back(Student(2, "Miki", 19));
  students.push_back(Student(3, "Maki", 20));

  // Serialization.
  TiXmlDocument xdoc;

  TiXmlDeclaration* xdec = new TiXmlDeclaration("1.0", "utf-8", "yes");
  xdoc.LinkEndChild(xdec);

  TiXmlComment* xcomment = new TiXmlComment("This is students info in a class!");
  xdoc.LinkEndChild(xcomment);

  TiXmlElement* xstudents = new TiXmlElement("Students");
  for (const Student& student : students) {
    TiXmlElement* xstudent = new TiXmlElement("Student");
    xstudent->SetAttribute("id", student.id);

    TiXmlElement* xname = new TiXmlElement("Name");
    TiXmlText* xname_text = new TiXmlText(student.name.c_str());
    xname->LinkEndChild(xname_text);
    xstudent->LinkEndChild(xname);

    TiXmlElement* xage = new TiXmlElement("Age");
    char age[32] = { 0 };
    sprintf(age, "%d", student.age);
    TiXmlText* xage_text = new TiXmlText(age);
    xage->LinkEndChild(xage_text);
    xstudent->LinkEndChild(xage);

    xstudents->LinkEndChild(xstudent);
  }

  xdoc.LinkEndChild(xstudents);

  TiXmlPrinter printer;
  xdoc.Accept(&printer);

  std::cout << printer.CStr() << std::endl;

  xdoc.SaveFile(kFileName);
}

static std::string GetElementText(TiXmlElement* element) {
  if (element == NULL) {
    return "";
  }

  const char* value = element->GetText();
  if (value == NULL) {
    return "";
  }

  return value;
}

static int GetElementIntValue(TiXmlElement* element) {
  std::string value_str = GetElementText(element);
  if (value_str.empty()) {
    return 0;
  }

  return atoi(value_str.c_str());
}

static void ReadData() {
  std::list<Student> students;

  TiXmlDocument xdoc;
  if (!xdoc.LoadFile(kFileName)) {
    return;
  }

  TiXmlElement* xstudents = xdoc.RootElement();
  if (xstudents == NULL) {
    return;
  }

  TiXmlElement* xstudent = xstudents->FirstChildElement();
  while (xstudent != NULL) {
    int id = 0;
    xstudent->QueryIntAttribute("id", &id);

    TiXmlElement* xname = xstudent->FirstChildElement("Name");
    std::string name = GetElementText(xname);

    TiXmlElement* xage = xstudent->FirstChildElement("Age");
    int age = GetElementIntValue(xage);

    students.push_back(Student(id, name, age));

    xstudent = xstudent->NextSiblingElement();
  }

  for (const Student& student : students) {
    student.Print();
  }
}

int main() {
  WriteData();
  ReadData();

  return 0;
}
