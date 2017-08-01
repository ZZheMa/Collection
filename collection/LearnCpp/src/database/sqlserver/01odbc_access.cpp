#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "windows.h"
#include "sql.h"
#include "sqlext.h"
#include "sqltypes.h"

// 1.参考：https://zh.wikipedia.org/zh-cn/ODBC，
//        http://www.cnblogs.com/kzang/archive/2012/11/29/2792447.html，
//        http://www.cnblogs.com/kzloser/archive/2012/11/29/2794815.html

// 2.Cmake中引入odbc32.lib。

// 3.使用odbc连接数据库有两种方法。
// (A)使用字符串连接。
// (B)使用odbc管理器连接。在管理器中创建一个DSN，将server名字，所访问的数据库名字等信息都填写正确。

// 4.odbc和sqlite3都提供了两种执行语句的方法，直接执行和prepare之后执行。

static void GetHstmtErrorMsg(SQLHSTMT hstmt) {
  SQLWCHAR error_msg[1024] = { 0 };
  SQLSMALLINT msg_len = 0;
  SQLWCHAR sql_state[6] = { 0 };
  SQLINTEGER error_code = 0;

  int i = 1;
  while (true) {
    if (SQLGetDiagRecW(SQL_HANDLE_STMT, hstmt, i, sql_state, &error_code, error_msg, 1024, &msg_len) != SQL_NO_DATA) {
      std::wcout<<error_msg<<std::endl;
    } else {
      break;
    }
    i++;
  }
}

// 直接执行sql。
static bool SelectData(SQLHDBC hdbc) {
  SQLHSTMT hstmt = SQL_NULL_HSTMT;

  // Allocate execute statement handle.
  SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to allocate execute statement handle!" << std::endl;
    return false;
  }

  SQLINTEGER id = 0;
  SQLSMALLINT age = 0;
  SQLCHAR name[50] = { 0 };
  SQLCHAR address[256] = { 0 };

  SQLWCHAR select_sql[256] = L"select * from students";
  ret = SQLExecDirect(hstmt, select_sql, SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to query data!" << std::endl;
  }

  // Bind column data.
  SQLBindCol(hstmt, 1, SQL_C_LONG, (void*)&id, sizeof(id), NULL);
  SQLBindCol(hstmt, 2, SQL_C_CHAR, (void*)&name, sizeof(name), NULL);
  SQLBindCol(hstmt, 3, SQL_C_SHORT, (void*)&age, sizeof(age), NULL);
  SQLBindCol(hstmt, 4, SQL_C_CHAR, (void*)&address, sizeof(address), NULL);

  while (SQLFetch(hstmt) != SQL_NO_DATA) {
    std::cout << "Id: " << id << "  Name: " << name << " Age: " << age << " Address: " << address << std::endl;
  }

  // Release execute statement handle.
  ret = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to release execute statement handle!" << std::endl;
  }

  return true;
}

// Prepare之后执行。
static bool InsertData(SQLHDBC hdbc) {
  SQLHSTMT hstmt = SQL_NULL_HSTMT;

  // Allocate execute statement handle.
  SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to allocate execute statement handle!" << std::endl;
    return false;
  }

  SQLSMALLINT age = 0;
  SQLCHAR name[50] = { 0 };  // 不能超过sqlserver中定义的varchar长度。
  SQLCHAR address[256] = { 0 };

  SQLWCHAR insert_sql[256] = L"insert into students(name, age, address) values(?,?,?)";

  ret = SQLPrepare(hstmt, insert_sql, SQL_NTS);
  if (ret != SQL_SUCCESS) {
    std::cout << "Failed to prepare sql!" << std::endl;
  }

  SQLINTEGER name_size = sizeof(name);
  ret = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name_size, 0, (void*)name, name_size, &name_size);
  ret = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, (void*)&age, 0, 0);
  SQLINTEGER address_size = sizeof(address);
  ret = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, address_size, 0, (void*)address, address_size, &address_size);

  age = 100;
  strcpy((char*)name, "Ma");
  strcpy((char*)address, "Maa");

  ret = SQLExecute(hstmt);
  if (ret != SQL_SUCCESS) {
    std::cout << "Failed to execute sql!" << std::endl;
  }

  age = 102;
  strcpy((char*)name, "Maz");
  strcpy((char*)address, "Maaz");

  ret = SQLExecute(hstmt);
  if (ret != SQL_SUCCESS) {
    std::cout << "Failed to execute sql!" << std::endl;
    GetHstmtErrorMsg(hstmt);
  }

  // Release execute statement handle.
  ret = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to release execute statement handle!" << std::endl;
  }

  return true;
}

int main() {
  SQLHENV henv = SQL_NULL_HENV;
  SQLHDBC hdbc = SQL_NULL_HDBC;

  // Allocate environment handle.
  SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to allocate environment handle!" << std::endl;
    return 1;
  }

  // Set the ODBC version environment attribute.
  ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to set the ODBC version environment attribute!" << std::endl;
    return 2;
  }

  // Allocate connection handle.
  ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to allocate connection handle!" << std::endl;
    return 3;
  }

  // Connect the sqlserver.
  bool use_odbc_management = false;
  
  if (use_odbc_management) {  // (A)使用odbc管理器连接。
    // DSN这个名字是odbc管理器中创建的DSN的名字，不是server或者数据库的名字。
    // 所要访问的server及数据库在管理器中配置。
    SQLWCHAR dsn[64] = L"Test";  // 使用windows认证登陆,所以不用写登录名和密码。
    ret = SQLConnect(hdbc, dsn, SQL_NTS, NULL, SQL_NTS, NULL, SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
      std::cout << "Failed to connect the sqlserver!" << std::endl;
      return 4;
    }
  } else {  // (B)使用字符串连接。
    SQLWCHAR out_string[1024];
    SQLSMALLINT out_len;
    SQLWCHAR dsn[256] = L"Driver={SQL Server};Server=CNSHWDW22B3X\\TROPHYSERVER;Database=test;Trusted_Connection=Yes;";
    ret = SQLDriverConnect(hdbc, NULL, dsn, SQL_NTS, out_string, 1024, &out_len, SQL_DRIVER_COMPLETE);;
  }

  SelectData(hdbc);
  InsertData(hdbc);
  SelectData(hdbc);

  // Disconnect sqlserver.
  ret = SQLDisconnect(hdbc);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to disconnect sqlserver!" << std::endl;
  }

  // Release connection handle.
  ret = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to release connection handle!" << std::endl;
  }

  // Release environment handle.
  ret = SQLFreeHandle(SQL_HANDLE_ENV, henv);
  if (!SQL_SUCCEEDED(ret)) {
    std::cout << "Failed to release environment handle!" << std::endl;
  }

  return 0;
}
