#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "soci.h"

// ʹ��soci����sqlite3.

// �ο� http://blog.csdn.net/littlewhite1989/article/details/54691367
// soci�ٷ��ĵ�test-sqlite3.cpp

// ������
static void CreateTable(soci::session& db) {
  db << "CREATE TABLE IF NOT EXISTS STUDENTS ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "NAME VARCHAR(50) NOT NULL,"
        "AGE INTEGER NOT NULL"
        ")";
}

// ��������
static void TestInsert(soci::session& db, const std::string& name, int age) {
  // 2.ֱ��ִ����䣬�൱�ڵ���sqlite3_exec(),ʹ��soci::use�����ݲ�����
  try {
    db << "INSERT INTO STUDENTS(NAME, AGE) VALUES(:name, :age)", soci::use(name), soci::use(age);
    } catch (const soci::soci_error& e) {
      std::cout << e.what() << std::endl;
      return;
    }
}

// ɾ������
static void TestDelete(soci::session& db, const std::string& name) {
  // 3.��prepare����SQL��䣬Ȼ����ִ�С�
  soci::statement stmt = (db.prepare << "DELETE FROM STUDENTS WHERE NAME = :name", soci::use(name));
  stmt.execute(true);
  long long affected_rows = stmt.get_affected_rows();
  std::cout << "Affected rows is " << affected_rows << "." << std::endl;
}

// �޸�����
static void TestUpdate(soci::session& db, const std::string& name, int age) {
  try {
    db << "UPDATE STUDENTS SET AGE = :age WHERE NAME = :name", soci::use(age), soci::use(name);
  } catch (const soci::soci_error& e) {
    std::cout << e.what() << std::endl;
    return;
  }
}

// ��ѯ����
static void TestSelect(soci::session& db, int id) {
  std::string name;
  int age = -1;

  try {
    db << "SELECT NAME, AGE FROM STUDENTS WHERE ID = :id", soci::use(id), soci::into(name), soci::into(age);
  } catch (const soci::soci_error& e) {
    std::cout << e.what() << std::endl;
  }

  if (!db.got_data()) {
    std::cout << "Select none!" << std::endl;
    return;
  }

  std::cout << "Id: " << id << ", Name: " << name << ", Age: " << age << std::endl;
}

// ��ʽ��������
static void TestTransaction(soci::session& db) {
  soci::transaction transaction(db);

  std::string name = "Zhe";
  for (int age = 0; age < 10000; ++age) {
    try {
      db << "INSERT INTO STUDENTS(NAME, AGE) VALUES(:name, :age)", soci::use(name), soci::use(age);
    } catch (const soci::soci_error& e) {
      std::cout << e.what() << std::endl;
      transaction.rollback();
      return;
    }
  }

  transaction.commit();
}

// TODO: ʹ��prepareִ�з�����û����ȷ��ʽ��������ִ���ٶȷǳ�����
static void FailedTestTransaction(soci::session& db) {
  soci::transaction transaction(db);
  soci::statement stmt = db.prepare << "INSERT INTO STUDENTS(NAME, AGE) VALUES(:name, :age)";

  for (int i = 0; i < 100; ++i) {
    std::string name = "Zhe";
    stmt.exchange(soci::use(name, "name"));
    stmt.exchange(soci::use(i, "age"));
    stmt.define_and_bind();
    stmt.execute(true);
  }

  transaction.commit();
}

// ͳ���ж���������
static long long TestCountAllRows(soci::session& db) {
  long long count = 0;

  try {
    db << "SELECT COUNT(*) FROM STUDENTS", soci::into(count);
  } catch (const soci::soci_error& e) {
    std::cout << e.what() << std::endl;
    return count;
  }

  std::cout << "The rows count is " << count << std::endl;

  return count;
}

// ��ѯ��������
static void TestSelectAll(soci::session& db) {
  soci::rowset<soci::row> rs = db.prepare << "SELECT * FROM STUDENTS";
  for (const soci::row& r : rs) {
    std::cout << "Id: " << r.get<int>(0);
    std::cout << ", Name: " << r.get<std::string>(1);
    std::cout << ", Age: " << r.get<int>(2) << std::endl;
  }
}

int main111() {
  // 1.�����ݿ⣬������ݿⲻ���ڣ��򴴽��ļ����ݿ�soci_test.db��
  soci::session db("sqlite3", "soci_test.db");

  CreateTable(db);

  TestDelete(db, "Zhe");
  TestInsert(db, "Zhe", 15);
  TestUpdate(db, "Zhe", 123);
  TestSelect(db, 1);

  TestCountAllRows(db);
  TestSelectAll(db);
  TestTransaction(db);
  FailedTestTransaction(db);

  return 0;
}
