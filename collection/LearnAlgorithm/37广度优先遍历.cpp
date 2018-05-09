#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <functional>
#include <algorithm>
#include <cassert>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void BFS(TreeNode* node) {
  if (node == NULL) {
    return;
  }

  std::queue<TreeNode*> node_queue;
  node_queue.push(node);

  while (!node_queue.empty()) {
    TreeNode* top_node = node_queue.front();
    std::cout << top_node->val << std::endl;

    if (top_node->left != NULL) {
      node_queue.push(top_node->left);
    }

    if (top_node->right != NULL) {
      node_queue.push(top_node->right);
    }

    node_queue.pop();
  }
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

  BFS(&node3);

  return 0;
}
