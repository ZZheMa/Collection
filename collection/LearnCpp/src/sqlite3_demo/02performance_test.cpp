#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <cstdio>

#include "sqlite3/sqlite3.h"
#include "utility/common.h"

// �ο���http://blog.csdn.net/majiakun1/article/details/46607163

static const char* kDatabaseName = "test.db";

//--------------------------------------------------------------

static void TestTimer();

//--------------------------------------------------------------

static bool PrepareDB(sqlite3** db, bool create_table);

static void CreateTable();

static void ClearTable();

static void TestExec(bool turn_off_synchronous = false);

static void TestNoSynchronous();

static void TestTransactionExec();

static void TestStep(bool turn_on_transaction = true);

static void PerformanceTest();

//--------------------------------------------------------------

int main2() {
  //TestTimer();
  ClearTable();
  //CreateTable();

  PerformanceTest();

  return 0;
}

//--------------------------------------------------------------

static void PerformanceTest() {
  //TestExec(false);
  //TestExec(true);
  TestNoSynchronous();
  //TestTransactionExec();
  //TestStep(true);
  //TestStep(false);
}

// 1.ֱ��ִ��sqlite3_exec��
static void TestExec(bool turn_off_synchronous) {
  sqlite3* db = NULL;
  if (!PrepareDB(&db, false)) {
    return;
  }

  if (turn_off_synchronous) {
    std::cout << "�ر�дͬ��ִ��sqlite3_exec : " << std::endl;
  } else {
    std::cout << "ֱ��ִ��sqlite3_exec : " << std::endl;
  }

  utility::Timer timer;
  std::stringstream sstream(std::stringstream::out);

  const int kDataCount = 100;
  const char* kTurnOffSynchronous = "PRAGMA synchronous = OFF;";

  if (turn_off_synchronous) {
    sqlite3_exec(db, kTurnOffSynchronous, NULL, NULL, NULL);
  }

  // Insert.
  timer.Start();
  for (int i = 0; i < kDataCount; ++i) {
    sstream << "INSERT INTO PERFORMANCE_TEST VALUES("
            << i << "," << i << "," << i << "," << i << ");";

    sqlite3_exec(db, sstream.str().c_str(), NULL, NULL, NULL);
    sstream.str("");
  }

  double rate = kDataCount / timer.GetSeconds();
  std::cout << "�������ݣ� " << rate <<"��/��" << std::endl;

  // Delete.
  timer.Start();
  for (int i = 0; i < kDataCount; ++i) {
    sstream << "DELETE FROM PERFORMANCE_TEST WHERE ID1 = " << i;
    sqlite3_exec(db, sstream.str().c_str(), NULL, NULL, NULL);
    sstream.str("");
  }

  rate = kDataCount / timer.GetSeconds();
  std::cout << "ɾ�����ݣ� " << rate << "��/��" << std::endl;

  sqlite3_close(db);
}

// 2.��ʽ��������ִ��sqlite3_exec��
// (A)��ν�����񡰾���ָһ��SQL�����Щ����Ҫôһ��ִ�У�Ҫô������ִ�С�
// (B)��SQLite�У�ÿ����һ��sqlite3_exec()�������ͻ���ʽ�ؿ�����һ�������������һ�����ݣ��͵��øú���һ�Σ�����ͻᱻ�����ؿ������رգ�������IO����
// (C)����ڲ�������ǰ��ʽ�������񣬲������һ���ύ����������IOЧ�ʣ����������ݿ�����ٶȡ�
static void TestTransactionExec() {
  sqlite3* db = NULL;
  if (!PrepareDB(&db, false)) {
    return;
  }

  std::cout << "��ʽ��������ִ��sqlite3_exec : " << std::endl;

  utility::Timer timer;
  std::stringstream sstream(std::stringstream::out);

  const int kDataCount = 10000;
  const char* kBeginTransaction = "begin";
  const char* kCommitTransaction = "commit";

  // Insert.
  timer.Start();
  sqlite3_exec(db, kBeginTransaction, NULL, NULL, NULL);
  for (int i = 0; i < kDataCount; ++i) {
    sstream << "INSERT INTO PERFORMANCE_TEST VALUES("
      << i << "," << i << "," << i << "," << i << ");";

    sqlite3_exec(db, sstream.str().c_str(), NULL, NULL, NULL);
    sstream.str("");
  }
  sqlite3_exec(db, kCommitTransaction, NULL, NULL, NULL);

  double rate = kDataCount / timer.GetSeconds();
  std::cout << "�������ݣ� " << rate << "��/��" << std::endl;

  // Delete.
  timer.Start();
  sqlite3_exec(db, kBeginTransaction, NULL, NULL, NULL);
  for (int i = 0; i < kDataCount; ++i) {
    sstream << "DELETE FROM PERFORMANCE_TEST WHERE ID1 = " << i;
    sqlite3_exec(db, sstream.str().c_str(), NULL, NULL, NULL);
    sstream.str("");
  }
  sqlite3_exec(db, kCommitTransaction, NULL, NULL, NULL);

  rate = kDataCount / timer.GetSeconds();
  std::cout << "ɾ�����ݣ� " << rate << "��/��" << std::endl;

  sqlite3_close(db);
}

// 3.�ر�дͬ������ʽ��������ִ��sqlite3_exec��
// (A)��SQLite�У����ݿ����õĲ������ɱ���ָʾ��pragma����ʵ�ֵġ�
// (B)synchronousѡ�������ֿ�ѡ״̬���ֱ���full��normal��off��
// ��synchronous����ΪFULL,SQLite���ݿ������ڽ���ʱ�̻���ͣ��ȷ�������Ѿ�д����̡���ʹϵͳ�������Դ������ʱ��ȷ�����ݿ�������󲻻��𻵡�FULL synchronous�ܰ�ȫ��������
// ��synchronous����ΪNORMAL, SQLite���ݿ������ڴ󲿷ֽ���ʱ�̻���ͣ��������FULLģʽ����ôƵ���� NORMALģʽ���к�С�ļ���(�����ǲ�����)������Դ���ϵ������ݿ��𻵵������
// ��ʵ���ϣ���������� �ºܿ������Ӳ���Ѿ�����ʹ�ã����߷����������Ĳ��ɻָ���Ӳ������
// ��Ϊsynchronous OFFʱ��SQLite�ڴ������ݸ�ϵͳ�Ժ�ֱ�Ӽ���������ͣ��������SQLite��Ӧ�ó�������� ���ݲ������ˣ�����ϵͳ������д������ʱ����ϵ硣
// (C)SQLite3�У���ѡ���Ĭ��ֵ����full����������ٲ�������ǰ�����Ϊoff��������Ч�ʡ�
static void TestNoSynchronous() {
  sqlite3* db = NULL;
  if (!PrepareDB(&db, false)) {
    return;
  }

  std::cout << "�ر�дͬ������ʽ��������ִ��sqlite3_exec : " << std::endl;

  utility::Timer timer;
  std::stringstream sstream(std::stringstream::out);

  const int kDataCount = 10000;
  const char* kTurnOffSynchronous = "PRAGMA synchronous = OFF;";
  const char* kBeginTransaction = "begin";
  const char* kCommitTransaction = "commit";

  sqlite3_exec(db, kTurnOffSynchronous, NULL, NULL, NULL);

  // Insert.
  timer.Start();
  sqlite3_exec(db, kBeginTransaction, NULL, NULL, NULL);
  for (int i = 0; i < kDataCount; ++i) {
    sstream << "INSERT INTO PERFORMANCE_TEST VALUES("
      << i << "," << i << "," << i << "," << i << ");";

    sqlite3_exec(db, sstream.str().c_str(), NULL, NULL, NULL);
    sstream.str("");
  }
  sqlite3_exec(db, kCommitTransaction, NULL, NULL, NULL);

  double rate = kDataCount / timer.GetSeconds();
  std::cout << "�������ݣ� " << rate << "��/��" << std::endl;

  // Delete.
  timer.Start();
  sqlite3_exec(db, kBeginTransaction, NULL, NULL, NULL);
  for (int i = 0; i < kDataCount; ++i) {
    sstream << "DELETE FROM PERFORMANCE_TEST WHERE ID1 = " << i;
    sqlite3_exec(db, sstream.str().c_str(), NULL, NULL, NULL);
    sstream.str("");
  }
  sqlite3_exec(db, kCommitTransaction, NULL, NULL, NULL);

  rate = kDataCount / timer.GetSeconds();
  std::cout << "ɾ�����ݣ� " << rate << "��/��" << std::endl;

  sqlite3_close(db);
}

// 4. ʹ��sqlite3_stepִ�С�
// (A)SQLiteִ��SQL����ʱ�������ַ�ʽ��һ����ʹ��ǰ���ᵽ�ĺ���sqlite3_exec()���ú���ֱ�ӵ��ð���SQL�����ַ�����
// ��һ�ַ������ǡ�ִ��׼�����������ڴ洢���̣����������Ƚ�SQL������ã�Ȼ����һ��һ������һ��һ�У���ִ�С�
// (B)�������ǰ�ߵĻ������㿪��������SQLite��ȻҪ��ѭ����ÿһ��SQL�����С��ʷ��������͡��﷨��������
// (C)��ִ��׼������Ҫ��Ϊ�����裺��������һ��ָ��sqlite3_stmt�����ָ�룬�ú����Բ�������SQL���zSql���б��룬��������״̬����ppStmt�С�
// ���ú��� sqlite3_step() �������������ִ��һ���������о��ǲ���һ�У�������������ص���SQLite_ROW��˵�����ڼ���ִ�У�������˵���Ѿ�ִ�������в�����
// ���ú��� sqlite3_finalize()���ر���䡣
// (D)������������SQLite��������Ч�����ķ�ʽ���ǣ�����+�ر�дͬ��+ִ��׼�����洢���̣�����������ݿⰲȫ����Ҫ��Ļ����Ϳ���дͬ����

static void TestStep(bool turn_on_transaction) {
  sqlite3* db = NULL;
  if (!PrepareDB(&db, false)) {
    return;
  }

  std::string title = "ֱ��ִ��sqlite3_step : ";
  if (turn_on_transaction) {
    title = "��ʽ��������ִ��sqlite3_step : ";
  }

  std::cout << title << std::endl;

  utility::Timer timer;

  int data_count = 20;
  if (turn_on_transaction) {
    data_count = 10000;
  }

  const char* kBeginTransaction = "begin";
  const char* kCommitTransaction = "commit";

  // Insert.
  timer.Start();
  if (turn_on_transaction) {
    sqlite3_exec(db, kBeginTransaction, NULL, NULL, NULL);
  }

  const char* kInsertSql = "INSERT INTO PERFORMANCE_TEST VALUES(?,?,?,?);";

  sqlite3_stmt* stmt = NULL;
  sqlite3_prepare_v2(db, kInsertSql, strlen(kInsertSql), &stmt, NULL);
  for (int i = 0; i < data_count; ++i) {
    sqlite3_reset(stmt);

    sqlite3_bind_int(stmt, 1, i);
    sqlite3_bind_int(stmt, 2, i);
    sqlite3_bind_int(stmt, 3, i);
    sqlite3_bind_int(stmt, 4, i);
    sqlite3_step(stmt);
  }

  if (turn_on_transaction) {
    sqlite3_exec(db, kCommitTransaction, NULL, NULL, NULL);
  }

  sqlite3_finalize(stmt);

  double rate = data_count / timer.GetSeconds();
  std::cout << "�������ݣ� " << rate << "��/��" << std::endl;

  // Delete.
  timer.Start();
  if (turn_on_transaction) {
    sqlite3_exec(db, kBeginTransaction, NULL, NULL, NULL);
  }

  const char* kDeleteSql = "DELETE FROM PERFORMANCE_TEST WHERE ID1 = ?;";
  sqlite3_prepare_v2(db, kDeleteSql, strlen(kDeleteSql), &stmt, NULL);
  for (int i = 0; i < data_count; ++i) {
    sqlite3_reset(stmt);

    sqlite3_bind_int(stmt, 1, i);
    sqlite3_step(stmt);
  }

  if (turn_on_transaction) {
    sqlite3_exec(db, kCommitTransaction, NULL, NULL, NULL);
  }

  sqlite3_finalize(stmt);

  rate = data_count / timer.GetSeconds();
  std::cout << "ɾ�����ݣ� " << rate << "��/��" << std::endl;

  sqlite3_close(db);
}

static bool PrepareDB(sqlite3** db, bool create_table) {
  int rc = sqlite3_open(kDatabaseName, db);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to open " << kDatabaseName << std::endl;
    std::cout << "Error msg: " << sqlite3_errmsg(*db) << std::endl;
    return false;
  }

  if (!create_table) {
    return true;
  }

  const char* kCreateTableSql = "CREATE TABLE PERFORMANCE_TEST(\
                                                                 ID1 INT, ID2 INT, ID3 INT, ID4 INT\
                                                                                                  );";
  char* error_msg = NULL;
  rc = sqlite3_exec(*db, kCreateTableSql, NULL, NULL, &error_msg);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to create table PERFORMANCE_TEST." << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
    return false;
  }

  return true;
}

static void CreateTable() {
  sqlite3* db = NULL;
  PrepareDB(&db, true);
  sqlite3_close(db);
}

static void ClearTable() {
  sqlite3* db = NULL;
  PrepareDB(&db, false);

  const char* kClrearTableSql = "DELETE FROM PERFORMANCE_TEST;";
  char* error_msg = NULL;

  int rc = sqlite3_exec(db, kClrearTableSql, NULL, NULL, &error_msg);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to clear table!" << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}
