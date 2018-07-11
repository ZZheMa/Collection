#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 538. Convert BST to Greater Tree

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void AccumulateNode(TreeNode* root, int& count) {
  if (root == NULL) {
    return;
  }

  // 中序遍历，先访问右节点，然后访问根节点，最后访问左节点。
  AccumulateNode(root->right, count);
  root->val += count;
  count = root->val;
  AccumulateNode(root->left, count);
}

TreeNode* convertBST(TreeNode* root) {
  int count = 0;
  AccumulateNode(root, count);
  return root;
}

void PreOrderPrint(TreeNode* root) {
  if (root == NULL) {
    return;
  }

  std::cout << root->val << ", ";
  PreOrderPrint(root->left);
  PreOrderPrint(root->right);
}

void InsertNode(TreeNode* root, TreeNode* node) {
  if (root == NULL) {
    return;
  }

  while (root != node) {
    if (node->val < root->val) {
      if (root->left == NULL) {
        root->left = node;
      } else {
        root = root->left;
      }
    } else {
      if (root->right == NULL) {
        root->right = node;
      } else {
        root = root->right;
      }
    }
  }
}

int main() {
  std::vector<int> nums{ 5, 4, 9, 8, 10 };
  TreeNode* head = new TreeNode(nums[0]);

  for (std::size_t i = 1; i < nums.size(); i++) {
    InsertNode(head, new TreeNode(nums[i]));
  }

  PreOrderPrint(head);
  std::cout << std::endl;

  PreOrderPrint(convertBST(head));
  std::cout << std::endl;

  return 0;
}
