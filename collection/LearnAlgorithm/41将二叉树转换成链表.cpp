#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 114. Flatten Binary Tree to Linked List

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void PreOrderDfs(TreeNode* root, std::vector<TreeNode*>& all_nodes) {
  if (root == NULL) {
    return;
  }

  all_nodes.push_back(root);
  PreOrderDfs(root->left, all_nodes);
  PreOrderDfs(root->right, all_nodes);
}

void flatten1(TreeNode* root) {
  if (root == NULL) {
    return;
  }

  std::vector<TreeNode*> all_nodes;
  PreOrderDfs(root, all_nodes);

  for (std::size_t i = 0; i < all_nodes.size() - 1; i++) {
    all_nodes[i]->left = NULL;
    all_nodes[i]->right = all_nodes[i + 1];
  }

  all_nodes.back()->right = NULL;
}

//----------------------------------------------------------

void PrintRightTree(TreeNode* root) {
  while (root != NULL) {
    std::cout << root->val << std::endl;
    root = root->right;
  }
}

int main() {
  TreeNode node1(1);
  TreeNode node2(2);
  TreeNode node3(3);
  TreeNode node4(4);
  TreeNode node5(5);
  TreeNode node6(6);

  node1.left = &node2;
  node2.left = &node3;
  node2.right = &node4;
  node1.right = &node5;
  node5.right = &node6;

  flatten1(&node1);
  PrintRightTree(&node1);

  return 0;
}
