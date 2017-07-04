#include "gtest/gtest.h"

#include <string>

//http://www.cnblogs.com/coderzh/archive/2009/04/06/1426755.html
//http://www.cnblogs.com/cutepig/archive/2009/03/15/1412640.html
//http://blog.csdn.net/skyflying2012/article/details/22668839

TEST(StringCmpTest, Demo) {
  char* pszCoderZh = "CoderZh";
  wchar_t* wszCoderZh = L"CoderZh";
  std::string strCoderZh = "CoderZh";
  std::wstring wstrCoderZh = L"CoderZh";

  EXPECT_STREQ("CoderZh", pszCoderZh);
  EXPECT_STREQ(L"CoderZh", wszCoderZh);
  EXPECT_STRNE("CnBlogs", pszCoderZh);
  EXPECT_STRNE(L"CnBlogs", wszCoderZh);
  EXPECT_STRCASEEQ("coderzh", pszCoderZh);
  EXPECT_STREQ("CoderZh", strCoderZh.c_str());
  EXPECT_STREQ(L"CoderZh", wstrCoderZh.c_str());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}