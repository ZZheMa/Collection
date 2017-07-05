#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <thread>

#include "sqlite3/sqlite3.h"

static const char* kDatabaseName = "test.db";

static void PrepareDatas(int start, int end, std::list<int>& datas) {
  for (int i = start; i <= end; ++i) {
    datas.push_back(i);
  }
}

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

  const char* kCreateTableSql = "CREATE TABLE CONCURRENCE_TEST(ID INT);";
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

static void InsertData(bool set_busy_handler, std::list<int> datas) {
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
    for (int data : datas) {
      sqlite3_reset(stmt);
      sqlite3_bind_int(stmt, 1, data);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE) {
        std::cout << "Failed to execute sql when insert " << data << "!" << std::endl;
        std::cout << "Error code: " << sqlite3_errcode(db) << std::endl;
        std::cout << "Error msg: " << sqlite3_errmsg(db) << std::endl;
        break;
      }
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

  std::list<int> datas1;
  std::list<int> datas2;
  PrepareDatas(1, 20, datas1);
  PrepareDatas(100, 120, datas2);

  // 1.不设置busy_handler。
  // 数据插入出错，一般情况下只能一个线程进行插入。当一个线程正在插入数据时，
  // 另一个线程插入插入时会返回错误，数据库已经被lock，插入失败，则该线程
  // 的数据不能成功插入。
  //std::thread thread1(InsertData, false, datas1);
  //std::thread thread2(InsertData, false, datas2);

  // 2.设置busy_handler。
  // 两个线程成功插入数据，当一个线程lock住数据库时，另一个线程执行失败
  // 返回SQLITE_BUSY，然后调用回调函数，回调函数返回0则retry，非零，则
  // 不进行retry，回调函数中的第二个参数是retry 的次数，在回调函数中可以
  // 加入每次retry等待的时间，也可以实现个timeout。
  // 实现了超时的set_busy_handler可以用sqlite3_busy_timeout来取代。
  std::thread thread1(InsertData, true, datas1);
  std::thread thread2(InsertData, true, datas2);

  thread1.join();
  thread2.join();

  return 0;
}
