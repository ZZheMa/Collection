#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "sqlite3/sqlite3.h"

static const char* kDatabaseName = "test.db";

static void OpenDB() {
  sqlite3* db = NULL;

  // The database is opened for reading and writing, and is created if it does not already exist. 
  // 如果数据库存在直接打开，如果不存在则创建之后再打开。打开方式为可读可写。
  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    int error_code = sqlite3_errcode(db);
    const char* error_msg = sqlite3_errmsg(db);

    std::cout << "Open failed!" << std::endl;
    std::cout << "Error code: " << error_code << std::endl;
    std::cout << "Error message: " << error_msg << std::endl;
    return;
  }

  std::cout << "Open successfully!" << std::endl;

  sqlite3_close(db);
}

static void CreateTable() {
  sqlite3* db = NULL;

  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    std::cout << sqlite3_errmsg(db) << std::endl;
  }

  rc = sqlite3_exec(db, NULL)

  sqlite3_close(db);
}

int main() {
  OpenDB();

  return 0;
}
