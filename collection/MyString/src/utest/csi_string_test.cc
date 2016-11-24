#include "gtest/gtest.h"
#include "str/csi_string.h"

TEST(CsiString_Test, DefaultConstructor) {
  const CsiString csi_str;
  EXPECT_STREQ("", csi_str.c_str());
  EXPECT_EQ(0u, csi_str.len());
  EXPECT_EQ(16u, csi_str.capacity());
}

const char kHelloCString[] = "Hello, CString!";
const CsiString HelloCsiString = "Hello, CsiString";

TEST(MyString, ConstructorFromCString) {
  const CsiString csi_str(kHelloCString);
  EXPECT_EQ(0, strcmp(csi_str.c_str(), kHelloCString));
  EXPECT_EQ(sizeof(kHelloCString) / sizeof(kHelloCString[0]) - 1,
            csi_str.len());
}

TEST(MyString, CopyConstructor) {
  const CsiString csi_str(HelloCsiString);
  EXPECT_EQ(0, strcmp(csi_str.c_str(), HelloCsiString.c_str()));
  EXPECT_EQ(HelloCsiString.len(), csi_str.len());
}
//
//// Tests the copy c'tor.
//TEST(MyString, CopyConstructor) {
//  const MyString s1(kHelloString);
//  const MyString s2 = s1;
//  EXPECT_EQ(0, strcmp(s2.c_string(), kHelloString));
//}
//
//// Tests the Set method.
//TEST(MyString, Set) {
//  MyString s;
//
//  s.Set(kHelloString);
//  EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
//
//  // Set should work when the input pointer is the same as the one
//  // already in the MyString object.
//  s.Set(s.c_string());
//  EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
//
//  // Can we set the MyString to NULL?
//  s.Set(NULL);
//  EXPECT_STREQ(NULL, s.c_string());
//}
