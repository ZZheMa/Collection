#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 315. Count of Smaller Numbers After Self

// 使用二叉查找树去求一组数的逆序数。

// 将者个数组逆序，也就是求某个数前面有几个比自己小的数。然后通过二叉查找树插入结点的过程，求得比插入结点小的结点的个数。

struct TreeNode {
  int value;
  int left_node_counts;  // 左子树的结点数。
  TreeNode* left;
  TreeNode* right;

  TreeNode(int val) : value(val), left_node_counts(0), left(nullptr), right(nullptr) {
  }
};


int InsertBstNode(TreeNode* root, TreeNode* node) {
  assert(root != nullptr && node != nullptr);

  int smaller_node_count = 0;

  while (root != node) {
    if (node->value > root->value) {
      // 在结点插入的过程中，插入结点大于正在比较的结点，也就是大于该结点的左子树的所有结点。
      smaller_node_count += root->left_node_counts + 1;

      if (root->right == nullptr) {
        root->right = node;
        break;
      } else {
        root = root->right;
      }
    } else {
      // 如果新插入的结点小于当前结点，则当前节点左子树的结点数加1。
      ++(root->left_node_counts);

      if (root->left == nullptr) {
        root->left = node;
        break;
      } else {
        root = root->left;
      }
    }
  }

  return smaller_node_count;
}

std::vector<int> countSmaller(const std::vector<int>& nums) {
  if (nums.empty()) {
    return {};
  }

  const std::size_t SIZE = nums.size();

  std::vector<TreeNode*> bst_nodes;
  for (int i = SIZE - 1; i >= 0; --i) {
    bst_nodes.push_back(new TreeNode(nums[i]));
  }

  std::vector<int> result(SIZE, 0);
  result[SIZE - 1] = 0;

  TreeNode* head = bst_nodes[0];
  for (std::size_t i = 1; i < bst_nodes.size(); ++i) {
    int smaller_node_count = InsertBstNode(head, bst_nodes[i]);
    result[SIZE - 1 - i] = smaller_node_count;
  }

  for (auto* node : bst_nodes) {
    delete node;
  }

  return result;
}

void PrintVec(std::vector<int>&& nums) {
  for (auto num : nums) {
    std::cout << num << ", ";
  }

  std::cout << std::endl;
}

int main() {
  PrintVec(countSmaller({ 5, 2, 6, 1 }));
  PrintVec(countSmaller({ 5, 2, 6, 1, 7, 3, 3, 3 }));

  return 0;
}
