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

// 199. Binary Tree Right Side View

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


std::vector<int> rightSideView(TreeNode* root) {
  typedef std::pair<TreeNode*, std::size_t /*layer*/> LayerNode;

  std::vector<int> right_view;

  if (root == NULL) {
    return right_view;
  }

  std::queue<LayerNode> layer_node_queue;
  layer_node_queue.push(std::make_pair(root, 0));

  while (!layer_node_queue.empty()) {
    LayerNode layer_node = layer_node_queue.front();
    layer_node_queue.pop();

    if (right_view.size() < layer_node.second + 1) {
      right_view.push_back(0);
    }

    right_view.back() = layer_node.first->val;

    if (layer_node.first->left != NULL) {
      layer_node_queue.push((std::make_pair(layer_node.first->left, layer_node.second + 1)));
    }

    if (layer_node.first->right != NULL) {
      layer_node_queue.push((std::make_pair(layer_node.first->right, layer_node.second + 1)));
    }
  }

  return right_view;
}

void PrintRightView(const std::vector<int>& nums) {
  for (int num : nums) {
    std::cout << num << std::endl;
  }
}

int main() {
  TreeNode node1(1);
  TreeNode node2(2);
  TreeNode node3(3);
  TreeNode node4(4);
  TreeNode node5(5);

  node1.left = &node2;
  node1.right = &node3;

  node2.right = &node5;
  node3.right = &node4;

  PrintRightView(rightSideView(&node1));

  return 0;
}
