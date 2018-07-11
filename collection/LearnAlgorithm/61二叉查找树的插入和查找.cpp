#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 二叉查找树

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int value;

  TreeNode(int val)
      : value(val)
      , left(nullptr)
      , right(nullptr) {
  }
};

void MidOrderPrint(TreeNode* root, int level = 0) {
  if (root == nullptr) {
    return;
  }

  MidOrderPrint(root->left, level + 1);

  std::cout << std::string(level, '-') << root->value << std::endl;

  MidOrderPrint(root->right, level + 1);
}

//--------------------------------------------------------------------
// 递归实现插入查找。

void Insert1(TreeNode* root, TreeNode* node) {
  if (node->value > root->value) {
    if (root->right == nullptr) {
      root->right = node;
    } else {
      Insert1(root->right, node);
    }
  } else {
    if (root->left == nullptr) {
      root->left = node;
    } else {
      Insert1(root->left, node);
    }
  }
}

bool Find1(TreeNode* root, int value) {
  if (root == nullptr) {
    return false;
  }

  if (value > root->value) {
    return Find1(root->right, value);
  } else if (value == root->value) {
    return true;
  } else {
    return Find1(root->left, value);
  }

  return false;
}

//--------------------------------------------------------------------
// 循环实现插入查找

void Insert2(TreeNode* root, TreeNode* node) {
  while (root != node) {
    if (node->value < root->value) {
      if (root->left == nullptr) {
        root->left = node;
        return;
      } else {
        root = root->left;
      }
    } else {
      if (root->right == nullptr) {
        root->right = node;
        return;
      } else {
        root = root->right;
      }
    }
  }
}

bool Find2(TreeNode* root, int value) {
  while (root != nullptr) {
    if (value > root->value) {
      root = root->right;
    } else if (value == root->value) {
      return true;
    } else {
      root = root->left;
    }
  }

  return false;
}

//--------------------------------------------------------------------

void Test1() {
  std::vector<TreeNode*> node_list{ new TreeNode(4), new TreeNode(2), new TreeNode(7),
                                    new TreeNode(1), new TreeNode(5), new TreeNode(3),
                                    new TreeNode(8) };

  TreeNode* head = node_list.front();
  for (std::size_t i = 1; i < node_list.size(); i++) {
    Insert1(head, node_list[i]);
  }

  MidOrderPrint(head);

  std::cout << Find1(head, 1) << std::endl;
  std::cout << Find1(head, 5) << std::endl;
  std::cout << Find1(head, 8) << std::endl;
  std::cout << Find1(head, 9) << std::endl;
  std::cout << Find1(head, 0) << std::endl;

  for (auto node : node_list) {
    delete node;
  }
}

void Test2() {
  std::vector<TreeNode*> node_list{ new TreeNode(4), new TreeNode(2), new TreeNode(7),
                                    new TreeNode(1), new TreeNode(5), new TreeNode(3),
                                    new TreeNode(8) };

  TreeNode* head = node_list.front();
  for (std::size_t i = 1; i < node_list.size(); i++) {
    Insert2(head, node_list[i]);
  }

  MidOrderPrint(head);

  std::cout << Find2(head, 1) << std::endl;
  std::cout << Find2(head, 5) << std::endl;
  std::cout << Find2(head, 8) << std::endl;
  std::cout << Find2(head, 9) << std::endl;
  std::cout << Find2(head, 0) << std::endl;

  for (auto node : node_list) {
    delete node;
  }
}

int main() {
  Test1();

  std::cout << std::endl;

  Test2();

  return 0;
}
