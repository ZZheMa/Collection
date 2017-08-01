#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

#include "windows.h"

#include "sqlite3/sqlite3.h"
#include "utility/common.h"

static const char* kDatabaseName = "test_primarykey.db";

static bool OpenDB(const char* path, sqlite3** db) {
  assert(db != NULL);

  int rc = sqlite3_open(path, db);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to open " << kDatabaseName << std::endl;
    std::cout << "Error msg: " << sqlite3_errmsg(*db) << std::endl;
    return false;
  }

  return true;
}

// 0:char32; 1:INT, 2: without rowid.
static std::string GetCreateTableSql(int type) {
  std::string sql = "CREATE TABLE ";

  if (type == 0) {
    sql += "CHAR32";
  } else if (type == 1) {
    sql += "INTEGER";
  } else if (type == 2) {
    sql += "WITHOUT_ROWID";
  }

  sql += "(";

  if (type == 1) {
    sql += "guid INTEGER PRIMARY KEY AUTOINCREMENT,";
  } else {
    sql += "guid char(32) NOT NULL PRIMARY KEY,";
  }

  sql += " text1 TEXT NOT NULL, text2 TEXT NOT NULL, text3 TEXT NOT NULL)";

  if (type == 2) {
    sql += "WITHOUT ROWID";
  }

  sql += ";";

  return sql;
}

static void PrepareTable() {
  sqlite3* db = NULL;

  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  for (int i = 0; i < 3; ++i) {
    char* error_msg = NULL;

    int rc = sqlite3_exec(db, GetCreateTableSql(i).c_str(), NULL, NULL, &error_msg);
    if (rc != SQLITE_OK) {
      std::cout << "Failed to create table!" << std::endl;
      std::cout << "Error msg: " << error_msg << std::endl;
      sqlite3_free(error_msg);
    }
  }

  sqlite3_close(db);
}


static void InsertData(int type) {
  utility::Timer timer;

  sqlite3* db = NULL;
  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  std::string insert_sql;
  if (type == 0) {
    insert_sql = "INSERT INTO char32 VALUES('%s', '%s', '%s', '%s');";
  } else if (type == 1) {
    insert_sql = "INSERT INTO integer VALUES('%d', '%s', '%s', '%s');";
  } else if (type == 2) {
    insert_sql = "INSERT INTO without_rowid VALUES('%s', '%s', '%s', '%s');";
  }

  timer.Start();

  sqlite3_exec(db, "begin", NULL, NULL, NULL);

  char sql[1024] = { 0 };
  GUID guid;
  for (int i = 0; i < 10000; i++) {
    CoCreateGuid(&guid);
    std::string s = utility::GuidToString(guid);
    if (type == 1) {
      sprintf(sql, insert_sql.c_str(), i, s.c_str(), s.c_str(), s.c_str());
    } else {
      sprintf(sql, insert_sql.c_str(), s.c_str(), s.c_str(), s.c_str(), s.c_str());
    }
    sqlite3_exec(db, sql, NULL, NULL, NULL);
  }

  sqlite3_exec(db, "commit", NULL, NULL, NULL);

  double time = timer.GetSeconds();

  std::cout << time << std::endl;

  sqlite3_close(db);
}

int main05() {
  DeleteFile(L"test_primarykey.db");

  PrepareTable();
  //ClearTable();
  for (int i = 0; i < 3; i++) {
    InsertData(i);
  }

  return 0;
}
