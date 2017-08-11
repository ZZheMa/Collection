#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "soci.h"

using namespace std;

// 参考 http://blog.csdn.net/littlewhite1989/article/details/54691367

// 1. 对象关系映射（Object Relational Mapping，简称ORM）模式是一种为了解决面向对象
// 与关系数据库存在的互不匹配的现象的技术。

static void CreateTable(soci::session& db) {
  db << "CREATE TABLE IF NOT EXISTS TEACHERS ("
    "ID INTEGER NOT NULL,"
    "NAME VARCHAR(50) NOT NULL,"
    "AGE INTEGER NOT NULL"
    ")";
}

struct TEACHER {
  int id;
  std::string name;
  int age;

  TEACHER()
      : id(-1)
      , age(-1) {
  }
};

std::ostream& operator<<(std::ostream& out, const TEACHER& teacher) {
  out << "Id: " << teacher.id << ", Name: " << teacher.name << ", Age: " << teacher.age;
  return out;
}

namespace soci {

template<>
struct type_conversion<TEACHER> {
  typedef values base_type;

  static void from_base(const values& v, indicator ind , TEACHER& teacher) {
    teacher.id = v.get<int>("ID");
    teacher.name = v.get<std::string>("NAME");
    teacher.age = v.get<int>("AGE");
  }

  static void to_base(const TEACHER& teacher, values& v, indicator& ind) {
    v.set("ID", teacher.id);
    v.set("NAME", teacher.name);
    v.set("AGE", teacher.age);
    ind = i_ok;
  }
};

}  // namespace soci

static void TestInsert(soci::session& db) {
  TEACHER teacher;
  teacher.id = 101;
  teacher.name = "Zhe";
  teacher.age = 10;

  // soci::use可直接使用对象teacher，会根据占位符指定字段。
  try {
    db << "INSERT INTO TEACHERS VALUES(:ID, :NAME, :AGE)", soci::use(teacher);
  } catch (const soci::soci_error& e) {
    std::cout << e.what() << std::endl;
    return;
  }
}

static void TestSelect(soci::session& db, int id) {
  TEACHER teacher;

  try {
    db << "SELECT * FROM TEACHERS WHERE ID = :id", soci::use(id), soci::into(teacher);
  } catch (const soci::soci_error& e) {
    std::cout << e.what() << std::endl;
    return;
  }

  std::cout << teacher << std::endl;
}

static void TestUpdate(soci::session& db, const TEACHER& teacher) {
  try {
    db << "UPDATE TEACHERS SET NAME=:NAME, AGE=:AGE WHERE ID=:ID", soci::use(teacher);
  } catch (const soci::soci_error& e) {
    cout << "err:" << e.what() << endl;
    return;
  }
}

static void TestDelete(soci::session& db, const TEACHER& teacher) {
  try {
    db << "DELETE FROM TEACHERS WHERE NAME=:NAME", soci::use(teacher);
  } catch (const soci::soci_error& e) {
    cout << "err:" << e.what() << endl;
    return;
  }
}

static void TestSelectAll(soci::session& db) {
  soci::rowset<TEACHER> teachers = db.prepare << "SELECT * FROM TEACHERS";
  for (const TEACHER& teacher : teachers) {
    std::cout << teacher << std::endl;
  }
}

int main002() {
  soci::session db("sqlite3", "soci_test.db");
  
  CreateTable(db);

  TestInsert(db);
  TestSelectAll(db);

  TestSelect(db, 101);

  TEACHER teacher;
  teacher.id = 101;
  teacher.name = "ZZZ";
  teacher.age = 111;
  TestUpdate(db, teacher);
  TestSelectAll(db);

  TestDelete(db, teacher);
  TestSelectAll(db);

  return 0;
}
