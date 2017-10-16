#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>

#include "sqlite3/sqlite3.h"
#include "utility/common.h"

// 测试数据库的打开和关闭对数据库性能的影响。

// 测试方法：
// 场景(A): 执行1000条写数据，一次打开数据库，一次关闭数据库。
// 场景(B): 执行1000条写数据，每次写都进行打开和关闭数据库。


static const char* kDatabaseName = "test.db";
static const char* kTurnOffSynchronous = "PRAGMA synchronous = OFF;";
static const char* kInsertSql = "INSERT INTO OPEN_CLOSE_COST_TEST(NAME) VALUES('Zhe');";
static const int kDataCount = 1000;

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

static void PrepareTable() {
  sqlite3* db = NULL;

  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  const char* kCreateTableSql = "CREATE TABLE IF NOT EXISTS OPEN_CLOSE_COST_TEST( \
                                 ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
                                 NAME TEXT NOT NULL)"; 
  char* error_msg = NULL;

  int rc = sqlite3_exec(db, kCreateTableSql, NULL, NULL, &error_msg);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to create table!" << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

static void ClearTable() {
  sqlite3* db = NULL;
  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  const char* kClearTableSql = "DELETE FROM OPEN_CLOSE_COST_TEST;";
  char* error_msg = NULL;

  int rc = sqlite3_exec(db, kClearTableSql, NULL, NULL, &error_msg);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to clear table!" << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

static void TestOnceOpenClose() {
  utility::Timer timer;
  timer.Start();

  sqlite3* db = NULL;
  sqlite3_open(kDatabaseName, &db);
  sqlite3_exec(db, kTurnOffSynchronous, NULL, NULL, NULL);

  for (int i = 0; i < kDataCount; ++i) {
    sqlite3_exec(db, kInsertSql, NULL, NULL, NULL);
  }

  sqlite3_close(db);

  std::cout << "1. 执行1000条写数据，一次打开数据库，一次关闭数据库: " << timer.GetSeconds() << std::endl;
}

static void TestMultiOpenClose() {
  utility::Timer timer;
  timer.Start();

  sqlite3* db = NULL;

  for (int i = 0; i < kDataCount; ++i) {
    sqlite3_open(kDatabaseName, &db);
    sqlite3_exec(db, kTurnOffSynchronous, NULL, NULL, NULL);

    sqlite3_exec(db, kInsertSql, NULL, NULL, NULL);
    
    sqlite3_close(db);
  }

  std::cout << "2. 执行1000条写数据，每次写都进行打开和关闭数据库: " << timer.GetSeconds() << std::endl;
}

int main() {
  PrepareTable();
  ClearTable();

  TestOnceOpenClose();
  TestMultiOpenClose();

  return 0;
}
