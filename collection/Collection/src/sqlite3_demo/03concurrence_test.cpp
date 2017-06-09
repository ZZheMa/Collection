#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <thread>

#include "sqlite3/sqlite3.h"

static const char* kDatabaseName = "test.db";

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

  const char* kCreateTableSql = "CREATE TABLE CONFURRENCE_TEST(ID INT);";
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

  const char* kClearTableSql = "DELETE FROM CONCURRENCE_TEST;";
  char* error_msg = NULL;

  int rc = sqlite3_exec(db, kClearTableSql, NULL, NULL, &error_msg);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to clear table!" << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

static int BusyHandler(void* ptr, int retry_times) {
  std::cout << "Retry " << retry_times << " times." << std::endl;

  sqlite3_sleep(10);

  // 如果返回零则不会继续等待，则外部的执行返回SQLITE_BUSY。
  // 如果返回非零则继续循环，等待其他应用释放DB锁。
  return 1;
}

static void InsertData(bool set_busy_handler) {
  sqlite3* db = NULL;
  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  if (set_busy_handler) {
    // sqlite3_busy_timeout
    sqlite3_busy_handler(db, BusyHandler, NULL);
  }

  const char* kInsertDataSql = "INSERT INTO CONCURRENCE_TEST VALUES(?);";

  sqlite3_stmt* stmt = NULL;
  int rc = sqlite3_prepare_v2(db, kInsertDataSql, strlen(kInsertDataSql), &stmt, NULL);
  if (rc == SQLITE_OK) {
    for (int i = 0; i < 10; ++i) {
      sqlite3_reset(stmt);
      sqlite3_bind_int(stmt, 1, i);
      sqlite3_step(stmt);
    }
  } else {
    std::cout << "Failed to prepare sql!" << std::endl;
    std::cout << "Error msg: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

int main() {
  //PrepareTable();

  ClearTable();
  return 0;
}
