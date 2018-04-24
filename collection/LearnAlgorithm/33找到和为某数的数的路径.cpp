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

// 充分理解二叉树的遍历。
// 先序：先根节点，然后左右节点。
// 中序：先左节点，然后根节点，最后右节点。
// 后序：先左右节点，然后根节点。

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void Traverse(TreeNode* node, int sum, int& temp_sum, std::vector<int>& subset, std::vector<std::vector<int>>& subsets) {
  // 判断当前节点是否为空，为空并不代表上一个节点或者当前节点为叶子节点。 该判断只说明其父节点的左或右子节点为空。
  if (node == NULL) {
    return;
  }

  // 因为要找到从根到叶子的整个路径，所以需要前序遍历，首先遍历根节点，将根节点放入subset。
  subset.push_back(node->val);
  temp_sum += node->val;

  Traverse(node->left, sum, temp_sum, subset, subsets);
  Traverse(node->right, sum, temp_sum, subset, subsets);

  // 判断当前节点为叶子节点，如果是叶子节点，则计算该路径的sum。
  if (node->left == NULL && node->right == NULL) {
    if (sum == temp_sum) {
      subsets.push_back(subset);
    }
  }

  // 后序遍历先遍历左右节点后遍历根节点，通过后序遍历来popup subset里面的值。
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
