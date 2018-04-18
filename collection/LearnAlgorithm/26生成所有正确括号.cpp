#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <set>
#include <cassert>

// 22. Generate Parentheses

// 本质：一棵二叉树递归遍历的变形。 

void Func(int i, int n, int left, int right, std::string str, std::vector<std::string>& result) {
  if (left < right) {
    return;
  }

  if (i >= n) {
    if (left == right) {
      result.push_back(str);
    }
    return;
  }

  Func(i + 1, n, left + 1, right, str + "(", result);
  Func(i + 1, n, left, right + 1, str + ")", result);
}

std::vector<std::string> generateParenthesis(int n) {
  std::vector<std::string> result;
  Func(0, 2 * n, 0, 0, "", result);

  return result;
}

void PrintResult(const std::vector<std::string>& result) {
  for (const auto& str : result) {
    std::cout << str << std::endl;
  }
}

int main() {
  PrintResult(generateParenthesis(3));

  return 0;
}
