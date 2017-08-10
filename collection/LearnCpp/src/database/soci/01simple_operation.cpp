#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "soci.h"

// 使用soci访问sqlite3.

static void CreateTable(soci::session& db) {
  db << "CREATE TABLE IF NOT EXISTS STUDENTS ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "NAME VARCHAR(50) NOT NULL,"
        "AGE INIEGER NOT NULL"
        ")";
}

static void TestInsert(soci::session& db, const std::string& name, int age) {
  // 2.直接执行语句，相当于调用sqlite3_exec(),使用soci::use来传递参数。
  try {
    std::string age1 = "111";
    //db << "INSERT INTO STUDENTS(NAME, AGE) VALUES(:name, :age)", soci::use(name), soci::use(age1);
    db << "INSERT INTO STUDENTS(NAME, AGE) VALUES('as', 155)";

    } catch (const soci::soci_error& e) {
      std::cout << e.what() << std::endl;
      return;
    }

    long id = -1;
    db.get_last_insert_id("STUDENTS", id);
    std::cout << "The last student id is " << id << "." << std::endl;
}

static void TestDelete(soci::session& db);
static void TestUpdate(soci::session& db);
static void TestSelect(soci::session& db);

static void TestTransaction(soci::session& db);

int main() {
  // 1.打开数据库，如果数据库不存在，则创建文件数据库soci_test.db。
  soci::session db("sqlite3", "soci_test.db");

  CreateTable(db);
  TestInsert(db, "Zhe", 15);

  return 0;
}
