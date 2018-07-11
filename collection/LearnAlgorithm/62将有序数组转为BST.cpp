#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 108. Convert Sorted Array to Binary Search Tree

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void InsertNodes(TreeNode* root, TreeNode* node) {
  while (root != node) {
    if (node->val < root->val) {
      if (root->left == nullptr) {
        root->left = node;
      } else {
        root = root->left;
      }
    } else {
      if (root->right == nullptr) {
        root->right = node;
      } else {
        root = root->right;
      }
    }
  }
}

void MidOrderPrint(TreeNode* root, int level = 0) {
  if (root == nullptr) {
    return;
  }

  MidOrderPrint(root->left, level + 2);
  std::cout << std::string(level, '-') << root->val << std::endl;
  MidOrderPrint(root->right, level + 2);
}

void FindBstNodes(const std::vector<int>& nums, int begin, int end, std::vector<TreeNode*>& bst_nodes) {
  if (begin > end) {
    return;
  }

  int mid = (begin + end) / 2;
  bst_nodes.push_back(new TreeNode(nums[mid]));

  FindBstNodes(nums, begin, mid - 1, bst_nodes);
  FindBstNodes(nums, mid + 1, end, bst_nodes);
}

// 二叉查找树的性质，任意结点的值大于左子树的值，小于右子树的值。

TreeNode* sortedArrayToBST(const std::vector<int>& nums) {
  if (nums.empty()) {
    return NULL;
  }

  std::vector<TreeNode*> bst_nodes;
  FindBstNodes(nums, 0, nums.size() - 1, bst_nodes);

  TreeNode* head = bst_nodes.front();
  for (std::size_t i = 1; i < bst_nodes.size(); i++) {
    InsertNodes(head, bst_nodes[i]);
  }

  return head;
}

int main() {
  MidOrderPrint(sortedArrayToBST({ -10, -3, 0, 5, 9 }));

  std::cout << std::endl;

  MidOrderPrint(sortedArrayToBST({ -11, -10, -3, 0, 5, 9, 10 }));


  return 0;
}
