#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "sqlite3/sqlite3.h"

static const char* kDatabaseName = "test.db";

static void OpenDB();
static void CreateTable();
static void InsertData();
static void SelectData();
static void UpdateData();
static void DeleteData();

int main1() {
  //OpenDB();
  //CreateTable();
  //InsertData();
  //SelectData();
  //UpdateData();
  //DeleteData();

  return 0;
}

static void OpenDB() {
  sqlite3* db = NULL;

  // The database is opened for reading and writing, and is created if it does not already exist. 
  // ������ݿ����ֱ�Ӵ򿪣�����������򴴽�֮���ٴ򿪡��򿪷�ʽΪ�ɶ���д��
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

  const char* kCreateTableSql = "CREATE TABLE COMPANY( \
                                 ID INT PRIMARY KEY NOT NULL, \
                                 NAME TEXT NOT NULL, \
                                 AGE INT NOT NULL, \
                                 ADDRESS CHAR(50), \
                                 SALARY REAL);";

  char* error_msg = NULL;
  // ���ʧ�ܻᶯ̬����һ��error_msg,ע��Ҫ�ֶ�free��
  rc = sqlite3_exec(db, kCreateTableSql, NULL, NULL, &error_msg);
  if (rc == SQLITE_OK) {
    std::cout << "Create Table COMPANY successfully!" << std::endl;
  } else {
    std::cout << "Create Table COMPANY failed!" << std::endl;
    std::cout << "Error msg: " << error_msg << std::endl;
    sqlite3_free(error_msg);
  }


  sqlite3_close(db);
}

static std::string InitInsertSql(const std::string& id,
                                 const std::string& name,
                                 const std::string& age,
                                 const std::string& address,
                                 const std::string& salary) {
  std::string sql = "INSERT INTO COMPANY(ID, NAME, AGE, ADDRESS, SALARY) VALUES(";
  sql += id + ", '" + name + "', " + age + ", '" + address + "', " + salary + ");";
  return sql.c_str();
}

static void InsertData() {
  sqlite3* db = NULL;

  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    std::cout << "Open " << kDatabaseName << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
  }

  std::string insert_sql = InitInsertSql("1", "Zhe", "18", "BeiJing", "1000");
  insert_sql += InitInsertSql("2", "Ma", "19", "ShangHai", "2000");
  insert_sql += InitInsertSql("3", "Miki", "20", "GuangZhou", "3000");
  insert_sql += InitInsertSql("4", "Li", "21", "ShenZhen", "4000");
  insert_sql += InitInsertSql("5", "Zhang", "22", "Wuhan", "5000");

  char* error_msg = NULL;
  rc = sqlite3_exec(db, insert_sql.c_str(), NULL, NULL, &error_msg);
  if (rc == SQLITE_OK) {
    std::cout << "Insert successfully!" << std::endl;
  } else {
    std::cout << "Insert failed! Error msg: " << error_msg << std::endl;
    sqlite3_free(db);
  }

  sqlite3_close(db);
}

//typedef int(*sqlite3_callback)(
//  void*,    /* Data provided in the 4th argument of sqlite3_exec() */
//  int,      /* The number of columns in row */
//  char**,   /* An array of strings representing fields in the row */
//  char**    /* An array of strings representing column names */
//  );
//  SQLite ��Ϊ SQL ������ִ�е�ÿ�� SELECT ����д����ÿ����¼��������ص�������
static int SelectCallback(void* data, int col_count, char** col_values, char** col_names) {
  for (int i = 0; i < col_count; ++i) {
    if (col_values[i] == NULL) {
      continue;
    }

    std::cout << col_names[i] << " = " << col_values[i] << std::endl;
  }

  const char* seperator = reinterpret_cast<const char*>(data);
  std::cout << seperator << std::endl;

  return 0;
}

static void SelectData() {
  sqlite3* db = NULL;

  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    std::cout << "Open " << kDatabaseName << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
  }

  const char* kSelectSql = "SELECT * FROM COMPANY;";
  const char* kSeperator = "================================";
  char* error_msg = NULL;

  rc = sqlite3_exec(db, kSelectSql, SelectCallback, (void*)kSeperator, &error_msg);
  if (rc == SQLITE_OK) {
    std::cout << "Select successfully!" << std::endl;
  } else {
    std::cout << "Select failed! Error msg: " << error_msg << std::endl;
    sqlite3_free(db);
  }

  sqlite3_close(db);
}

// sqlite3_exec����ִ�ж�����䣬�ص������������е�select��䡣
static void UpdateData() {
  sqlite3* db = NULL;

  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    std::cout << "Open " << kDatabaseName << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
  }

  const char* kSelectSql = "UPDATE COMPANY SET SALARY = 9999 WHERE ID = 1; SELECT * FROM COMPANY;";
  const char* kSeperator = "================================";
  char* error_msg = NULL;

  rc = sqlite3_exec(db, kSelectSql, SelectCallback, (void*)kSeperator, &error_msg);
  if (rc == SQLITE_OK) {
    std::cout << "Update successfully!" << std::endl;
  } else {
    std::cout << "Update failed! Error msg: " << error_msg << std::endl;
    sqlite3_free(db);
  }

  sqlite3_close(db);
}

static void DeleteData() {
  sqlite3* db = NULL;

  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    std::cout << "Open " << kDatabaseName << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
  }

  const char* kSelectSql = "DELETE FROM COMPANY WHERE ID = 4; SELECT * FROM COMPANY;";
  const char* kSeperator = "================================";
  char* error_msg = NULL;

  rc = sqlite3_exec(db, kSelectSql, SelectCallback, (void*)kSeperator, &error_msg);
  if (rc == SQLITE_OK) {
    std::cout << "Delete successfully!" << std::endl;
  } else {
    std::cout << "Delete failed! Error msg: " << error_msg << std::endl;
    sqlite3_free(db);
  }

  sqlite3_close(db);
}
