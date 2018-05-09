#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 236. Lowest Common Ancestor of a Binary Tree

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void FindPath(TreeNode* root, TreeNode* dst_node, std::vector<TreeNode*>& path) {
  if (root == NULL) {
    return;
  }

  if (!path.empty() && path.back() == dst_node) {
    return;
  }

  path.push_back(root);

  FindPath(root->left, dst_node, path);
  FindPath(root->right, dst_node, path);

  if (!path.empty() && path.back() == dst_node) {
    return;
  }

  path.pop_back();
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  std::vector<TreeNode*> p_path;
  FindPath(root, p, p_path);

  std::vector<TreeNode*> q_path;
  FindPath(root, q, q_path);

  TreeNode* common_ancestor = NULL;
  for (std::size_t i = 0; i < p_path.size() && i < q_path.size(); ++i) {
    if (p_path[i] == q_path[i]) {
      common_ancestor = p_path[i];
    } else {
      break;
    }
  }

  return common_ancestor;
}

int main() {
  TreeNode node3(3);
  TreeNode node5(5);
  TreeNode node1(1);
  TreeNode node6(6);
  TreeNode node2(2);
  TreeNode node0(0);
  TreeNode node8(8);
  TreeNode node7(7);
  TreeNode node4(4);

  node3.left = &node5;
  node3.right = &node1;
  node5.left = &node6;
  node5.right = &node2;
  node1.left = &node0;
  node1.right = &node8;
  node2.left = &node7;
  node2.right = &node4;

  TreeNode* ancestor1 = lowestCommonAncestor(&node3, &node5, &node1);
  std::cout << ancestor1->val << std::endl;;

  TreeNode* ancestor2 = lowestCommonAncestor(&node3, &node5, &node4);
  std::cout << ancestor2->val << std::endl;;

  return 0;
}
