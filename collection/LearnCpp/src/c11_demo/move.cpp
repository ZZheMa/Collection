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

  // 注意：一个对象被移动之后，要确保其还能正常的进行析构函数。
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

    // 深拷贝。
    size_t len = strlen(student.name_);
    name_ = new char[len + 1];
    strcpy(name_, student.name_);
  }

  Student(Student&& student) {
    std::cout << "Move Constructor" << std::endl;

    // 浅拷贝。
    // 将右值移动到新值上。
    id_ = student.id_;
    name_ = student.name_;

    // 右值则指向空。
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

  PrintStudent(a);  // 调用拷贝构造

  PrintStudent(Student(2, "2"));  // 既没有移动构造也没有拷贝构造，而是直接将临时对象变为函数的参数。

  PrintStudent(std::move(Student(2, "2")));  // 调用移动构造。

  PrintStudent(std::move(a));  // 调用移动构造
  a.Print();  // 原来的对象被移动。

  Student a2 = GetStudent();  // 调用依次移动构造。

  Student a3;
  a3 = Student(3, "3");  // 调用移动赋值运算符。

  Student a4(4, "4");
  a3 = a4;  // 调用拷贝构造函数。

  a3 = std::move(a4);  // 调用移动赋值运算符。

  a3 = GetStudent();  // 调用移动赋值运算符。

  return 0;
}

// 1.C++11提供了移动语义，分别是移动构造函数和移动赋值运算符，那么什么时候会触发移动语义？
// (A). 类必须定义了移动构造函数和移动赋值运算符。
// (B). 触发移动语义：
//      对于移动构造函数：函数返回把临时对象当做返回值，使用std::move。
//      对于移动赋值运算符：函数返回把临时对象当做返回值，使用std::move,临时对象。

// 2. std::move是标准库函数，它并不是移动了什么，而是返回变量的右值引用。这样就明确指定了一个右值引用，
// 所以会触发移动语义。

// 3.注意：一个对象被移动之后，要确保其还能正常的进行析构函数。

// 4.问题：当给函数传递对象当做函数参数时，可以使用引用类型来减少拷贝对象的代价，尤其是避免容器的拷贝等。
// 但是当把函数内的局部对象当做返回值时，我们无法返回该局部对象的引用，导致每次返回局部对象都会进行拷贝。
// 因为返回局部对象的引用是无意义的，当函数调用完成，局部对象就被析构，所以其引用指向了一块析构的内存。

// 解决方案一： 将输出作为函数参数，例如：
// void GetStudents(std::vector<int>* students) {
//   students->push_back(1);
//   students->push_back(2);
// }
// 解决方案二： C++11的移动语义解决了这个问题。函数返回的临时变量被当做初始值或者赋值操作符右侧的运算对象时，
// 程序使用移动操作，避免了拷贝，将新变量指向了局部变量的内容。例如
//  std::vector<int> GetNums() {
//    std::vector<int> nums;
//    nums.push_back(1);
//    nums.push_back(2);
//    return nums;
//  }
//  
//  std::vector<int> result = GetNums();  // 调用vector的移动构造函数，避免了拷贝。

// 5.标准库的容器vector，string等实现了拷贝语义，所以这些容器作为函数的局部对象时都可以直接返回。
