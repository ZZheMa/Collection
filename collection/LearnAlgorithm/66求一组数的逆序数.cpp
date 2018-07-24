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

// ʹ�ö��������ȥ��һ��������������

// ���߸���������Ҳ������ĳ����ǰ���м������Լ�С������Ȼ��ͨ�����������������Ĺ��̣���ñȲ�����С�Ľ��ĸ�����

struct TreeNode {
  int value;
  int left_node_counts;  // �������Ľ������
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
      // �ڽ�����Ĺ����У�������������ڱȽϵĽ�㣬Ҳ���Ǵ��ڸý��������������н�㡣
      smaller_node_count += root->left_node_counts + 1;

      if (root->right == nullptr) {
        root->right = node;
        break;
      } else {
        root = root->right;
      }
    } else {
      // ����²���Ľ��С�ڵ�ǰ��㣬��ǰ�ڵ��������Ľ������1��
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
