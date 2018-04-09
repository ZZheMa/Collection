#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

class Student {
public:
  Student() {
    id_ = 0;
    name_ = nullptr;
  }

  Student(int id, const char* name) {
    id_ = id;
    size_t len = strlen(name);
    name_ = new char[len + 1];
    strcpy(name_, name);
  }

  // ע�⣺һ�������ƶ�֮��Ҫȷ���仹�������Ľ�������������
  ~Student() {
    id_ = 0;
    if (name_ != nullptr) {
      delete[] name_;
      name_ = nullptr;
    }
  }

  Student(const Student& student) {
    std::cout << "Copy Constructor" << std::endl;

    id_ = student.id_;

    // �����
    size_t len = strlen(student.name_);
    name_ = new char[len + 1];
    strcpy(name_, student.name_);
  }

  Student(Student&& student) {
    std::cout << "Move Constructor" << std::endl;

    // ǳ������
    // ����ֵ�ƶ�����ֵ�ϡ�
    id_ = student.id_;
    name_ = student.name_;

    // ��ֵ��ָ��ա�
    student.id_ = 0;
    student.name_ = nullptr;
  }

  Student& operator=(const Student& student) {
    std::cout << "Copy Assignment" << std::endl;

    if (this == &student) {
      return *this;
    }

    id_ = student.id_;

    size_t len = strlen(student.name_);
    name_ = new char[len + 1];
    strcpy(name_, student.name_);

    return *this;
  }

  Student& operator=(Student&& student) {
    std::cout << "Move Assignment" << std::endl;

    if (this == &student) {
      return *this;
    }

    if (name_ != nullptr) {
      delete[] name_;
    }

    id_ = student.id_;
    name_ = student.name_;

    student.id_ = 0;
    student.name_ = nullptr;

    return *this;
  }

  void Print() {
    std::cout << id_ << " : " << (name_ == nullptr ? "NULL": name_) << std::endl;
  }

private:
  int id_;
  char* name_;
};

void PrintStudent(Student student) {
  student.Print();
}

Student GetStudent() {
  Student student(123, "123");
  return student;
}

int main() {
  Student a(1, "1");

  PrintStudent(a);  // ���ÿ�������

  PrintStudent(Student(2, "2"));  // ��û���ƶ�����Ҳû�п������죬����ֱ�ӽ���ʱ�����Ϊ�����Ĳ�����

  PrintStudent(std::move(Student(2, "2")));  // �����ƶ����졣

  PrintStudent(std::move(a));  // �����ƶ�����
  a.Print();  // ԭ���Ķ����ƶ���

  Student a2 = GetStudent();  // ���������ƶ����졣

  Student a3;
  a3 = Student(3, "3");  // �����ƶ���ֵ�������

  Student a4(4, "4");
  a3 = a4;  // ���ÿ������캯����

  a3 = std::move(a4);  // �����ƶ���ֵ�������

  a3 = GetStudent();  // �����ƶ���ֵ�������

  return 0;
}

// 1.C++11�ṩ���ƶ����壬�ֱ����ƶ����캯�����ƶ���ֵ���������ôʲôʱ��ᴥ���ƶ����壿
// (A). ����붨�����ƶ����캯�����ƶ���ֵ�������
// (B). �����ƶ����壺
//      �����ƶ����캯�����������ذ���ʱ����������ֵ��ʹ��std::move��
//      �����ƶ���ֵ��������������ذ���ʱ����������ֵ��ʹ��std::move,��ʱ����

// 2. std::move�Ǳ�׼�⺯�������������ƶ���ʲô�����Ƿ��ر�������ֵ���á���������ȷָ����һ����ֵ���ã�
// ���Իᴥ���ƶ����塣

// 3.ע�⣺һ�������ƶ�֮��Ҫȷ���仹�������Ľ�������������

// 4.���⣺�����������ݶ�������������ʱ������ʹ���������������ٿ�������Ĵ��ۣ������Ǳ��������Ŀ����ȡ�
// ���ǵ��Ѻ����ڵľֲ�����������ֵʱ�������޷����ظþֲ���������ã�����ÿ�η��ؾֲ����󶼻���п�����
// ��Ϊ���ؾֲ������������������ģ�������������ɣ��ֲ�����ͱ�����������������ָ����һ���������ڴ档

// �������һ�� �������Ϊ�������������磺
// void GetStudents(std::vector<int>* students) {
//   students->push_back(1);
//   students->push_back(2);
// }
// ����������� C++11���ƶ���������������⡣�������ص���ʱ������������ʼֵ���߸�ֵ�������Ҳ���������ʱ��
// ����ʹ���ƶ������������˿��������±���ָ���˾ֲ����������ݡ�����
//  std::vector<int> GetNums() {
//    std::vector<int> nums;
//    nums.push_back(1);
//    nums.push_back(2);
//    return nums;
//  }
//  
//  std::vector<int> result = GetNums();  // ����vector���ƶ����캯���������˿�����

// 5.��׼�������vector��string��ʵ���˿������壬������Щ������Ϊ�����ľֲ�����ʱ������ֱ�ӷ��ء�
