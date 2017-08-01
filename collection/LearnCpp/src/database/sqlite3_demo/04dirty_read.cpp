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

  sqlite3_enable_shared_cache(1);

  int rc = sqlite3_open(path, db);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to open " << kDatabaseName << std::endl;
    std::cout << "Error msg: " << sqlite3_errmsg(*db) << std::endl;
    return false;
  }

  sqlite3_exec(*db, "PRAGMA read_uncommitted = TRUE", NULL, NULL, NULL);

  return true;
}

static void PrepareTable() {
  sqlite3* db = NULL;

  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  const char* kCreateTableSql = "CREATE TABLE DIRTYREAD_TEST(ID INT);";
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

  const char* kClearTableSql = "DELETE FROM DIRTYREAD_TEST;";
  char* error_msg = NULL;

  int rc = sqlite3_exec(db, kClearTableSql, NULL, NULL, &error_msg);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to clear table!" << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

static void InsertData() {
  sqlite3* db = NULL;
  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  const char* kInsertDataSql = "INSERT INTO DIRTYREAD_TEST VALUES(?);";

  sqlite3_exec(db, "begin", NULL, NULL, NULL);

  sqlite3_stmt* stmt = NULL;
  sqlite3_prepare_v2(db, kInsertDataSql, strlen(kInsertDataSql), &stmt, NULL);

  for (int i = 0; i < 10000000; i++) {
    sqlite3_reset(stmt);
    sqlite3_bind_int(stmt, 1, i);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
      std::cout << "Failed to execute sql when insert " << i << "!" << std::endl;
      std::cout << "Error code: " << sqlite3_errcode(db) << std::endl;
      std::cout << "Error msg: " << sqlite3_errmsg(db) << std::endl;
      break;
    }
  }

  sqlite3_finalize(stmt);

  sqlite3_exec(db, "commit", NULL, NULL, NULL);

  sqlite3_close(db);
}

static int SelectCallback(void* data, int col_count, char** col_values, char** col_names) {
  for (int i = 0; i < col_count; ++i) {
    if (col_values[i] == NULL) {
      continue;
    }

    std::cout << col_names[i] << " = " << col_values[i] << std::endl;
  }

  return 0;
}

static void ReadData() {
  sqlite3* db = NULL;
  if (!OpenDB(kDatabaseName, &db)) {
    return;
  }

  const char* kSelectSql = "SELECT * FROM DIRTYREAD_TEST WHERE ID = 1;";
  char* error_msg = NULL;

  for (int i = 0; i < 1000; i++) {
    int rc = sqlite3_exec(db, kSelectSql, SelectCallback, NULL, &error_msg);
    if (rc == SQLITE_OK) {
      std::cout << "Select successfully!" << std::endl;
    } else {
      std::cout << "Select failed! Error msg: " << error_msg << std::endl;
      sqlite3_free(error_msg);
    }
  }

  sqlite3_close(db);
}

int main4() {
  //PrepareTable();
  ClearTable();

  std::thread thread1(InsertData);
  std::thread thread2(ReadData);

  thread1.join();
  thread2.join();

  return 0;
}
