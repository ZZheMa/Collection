#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "soci.h"

// 1. π”√soci∑√Œ sqlite3.

static void CreateTable(soci::session& db) {
  db << "CREATE TABLE IF NOT EXISTS STUDENTS ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "NAME VARCHAR(50) NOT NULL,"
        "AGE INIEGER NOT NULL"
        ")";
}

static void TestInsert(soci::session& db);
static void TestDelete(soci::session& db);
static void TestUpdate(soci::session& db);
static void TestSelect(soci::session& db);

static void TestTransaction(soci::session& db);

int main() {
  soci::session db("sqlite3", "soci_test.db");

  CreateTable(db);


  return 0;
}
