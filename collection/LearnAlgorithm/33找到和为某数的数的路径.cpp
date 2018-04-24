#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cassert>

// 113. Path Sum II

// ������������ı�����
// �����ȸ��ڵ㣬Ȼ�����ҽڵ㡣
// ��������ڵ㣬Ȼ����ڵ㣬����ҽڵ㡣
// ���������ҽڵ㣬Ȼ����ڵ㡣

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void Traverse(TreeNode* node, int sum, int& temp_sum, std::vector<int>& subset, std::vector<std::vector<int>>& subsets) {
  // �жϵ�ǰ�ڵ��Ƿ�Ϊ�գ�Ϊ�ղ���������һ���ڵ���ߵ�ǰ�ڵ�ΪҶ�ӽڵ㡣 ���ж�ֻ˵���丸�ڵ��������ӽڵ�Ϊ�ա�
  if (node == NULL) {
    return;
  }

  // ��ΪҪ�ҵ��Ӹ���Ҷ�ӵ�����·����������Ҫǰ����������ȱ������ڵ㣬�����ڵ����subset��
  subset.push_back(node->val);
  temp_sum += node->val;

  Traverse(node->left, sum, temp_sum, subset, subsets);
  Traverse(node->right, sum, temp_sum, subset, subsets);

  // �жϵ�ǰ�ڵ�ΪҶ�ӽڵ㣬�����Ҷ�ӽڵ㣬������·����sum��
  if (node->left == NULL && node->right == NULL) {
    if (sum == temp_sum) {
      subsets.push_back(subset);
    }
  }

  // ��������ȱ������ҽڵ��������ڵ㣬ͨ�����������popup subset�����ֵ��
  if (!subset.empty()) {
    temp_sum -= node->val;
    subset.pop_back();
  }
}

std::vector<std::vector<int>> pathSum(TreeNode* root, int sum) {
  std::vector<std::vector<int>> subsets;
  std::vector<int> subset;
  int temp_sum = 0;
  Traverse(root, sum, temp_sum, subset, subsets);

  return subsets;
}

void PrintSubsets(std::vector<std::vector<int>> subsets) {
  for (const auto& subset : subsets) {
    for (auto num : subset) {
      std::cout << num << " ";
    }

    std::cout << std::endl;
  }
}

int main() {
  TreeNode node1(5);
  TreeNode node2(4);
  TreeNode node3(8);
  TreeNode node4(11);
  TreeNode node5(13);
  TreeNode node6(4);
  TreeNode node7(7);
  TreeNode node8(2);
  TreeNode node9(5);
  TreeNode node10(1);

  node1.left = &node2;
  node1.right = &node3;

  node2.left = &node4;

  node4.left = &node7;
  node4.right = &node8;

  node3.left = &node5;
  node3.right = &node6;

  node6.left = &node9;
  node6.right = &node10;

  PrintSubsets(pathSum(&node1, 22));


//       5
//     / \
//    4   8
//   /   / \
//  11  13  4
// /  \    / \
//7    2  5   1
  return 0;
}
