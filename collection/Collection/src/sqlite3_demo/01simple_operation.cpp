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
static void StepExecute();

int main() {
  //OpenDB();
  //CreateTable();
  //InsertData();
  //SelectData();
  //UpdateData();
  //DeleteData();
  //StepExecute();
  return 0;
}

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

  const char* kCreateTableSql = "CREATE TABLE COMPANY( \
                                 ID INT PRIMARY KEY NOT NULL, \
                                 NAME TEXT NOT NULL, \
                                 AGE INT NOT NULL, \
                                 ADDRESS CHAR(50), \
                                 SALARY REAL);";

  char* error_msg = NULL;
  // 如果失败会动态分配一个error_msg,注意要手动free。
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
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

//typedef int(*sqlite3_callback)(
//  void*,    /* Data provided in the 4th argument of sqlite3_exec() */
//  int,      /* The number of columns in row */
//  char**,   /* An array of strings representing fields in the row */
//  char**    /* An array of strings representing column names */
//  );
//  SQLite 将为 SQL 参数内执行的每个 SELECT 语句中处理的每个记录调用这个回调函数。
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
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

// sqlite3_exec可以执行多条语句，回调函数用于其中的select语句。
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
    sqlite3_free(error_msg);
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
    sqlite3_free(error_msg);
  }

  sqlite3_close(db);
}

// The statement sqlite3_step is evaluated up to the point where the first row of results are available.
// To advance to the second row of results, invoke sqlite3_step() again.
// 1.如果SQL语句执行成功或者正常将返回SQLITE_DONE, 否则将返回错误代码。
// 2.如果SQL返回了一个单行结果集，sqlite3_step() 函数将返回 SQLITE_ROW,然后继续调用sqlite3_step来得到下一个结果。
// 3.如果不能打开数据库文件则会返回 SQLITE_BUSY。
static void StepExecute() {
  sqlite3* db = NULL;

  int rc = sqlite3_open(kDatabaseName, &db);
  if (rc != SQLITE_OK) {
    std::cout << "Open " << kDatabaseName << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
  }

  const char* kSelectSql = "SELECT * FROM COMPANY WHERE ID = ? OR ID = ?;";

  sqlite3_stmt* stmt = NULL;
  // sqlite3_prepare2 接口把一条SQL语句编译成字节码留给后面的执行函数。
  rc = sqlite3_prepare_v2(db, kSelectSql, strlen(kSelectSql), &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cout << "Failed to prepare sql!" << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // sqlite3_bind 所包含的全部接口，它们是用来给SQL声明中的通配符赋值的。
  sqlite3_bind_int(stmt, 1, 2);
  sqlite3_bind_int(stmt, 2, 3);

  do {
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR) {
      std::cout << "Failed to step execute!" << std::endl;
      break;
    }

    if (rc == SQLITE_DONE) {
      std::cout << "Finished to step execute!" << std::endl;
      break;
    }

    int column_count = sqlite3_column_count(stmt);
    for (int i = 0; i < column_count; ++i) {
      const unsigned char* column_value = sqlite3_column_text(stmt, i);
      if (column_value == NULL) {
        continue;
      }

      std::cout << sqlite3_column_name(stmt, i) << " = " << column_value << std::endl;
    }

    std::cout << "=====================================" << std::endl;
  } while (rc == SQLITE_ROW);

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}
