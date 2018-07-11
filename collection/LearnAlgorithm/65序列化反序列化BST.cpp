#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 449. Serialize and Deserialize BST.

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//----------------------------------------------------

void PreOrderEncode(TreeNode* root, std::string& data) {
  if (root == NULL) {
    return;
  }

  data += std::to_string(root->val);
  data += "#";

  PreOrderEncode(root->left, data);
  PreOrderEncode(root->right, data);
}

// Encodes a tree to a single string.
std::string Serialize(TreeNode* root) {
  std::string data;
  PreOrderEncode(root, data);

  return data;
}

//-------------------------------------------------

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

// Decodes an encoded data to tree.
TreeNode* Deserialize(const std::string& data) {
  std::vector<TreeNode*> nodes;

  std::size_t begin = 0;
  std::size_t pos = 0;

  while (true) {
    std::size_t pos = data.find('#', begin);
    if (pos == std::string::npos) {
      break;
    }

    std::string num = data.substr(begin, pos - begin);
    nodes.push_back(new TreeNode(std::stoi(num)));

    begin = pos + 1;
  }

  if (nodes.empty()) {
    return NULL;
  }

  for (std::size_t i = 1; i < nodes.size(); i++) {
    InsertNode(nodes[0], nodes[i]);
  }

  return nodes[0];
}

void PreOrderPrint(TreeNode* root) {
  if (root == NULL) {
    return;
  }

  std::cout << root->val << ", ";
  PreOrderPrint(root->left);
  PreOrderPrint(root->right);
}

int main() {
  std::vector<int> nums{ 5, 4, 9, 8, 10 };
  TreeNode* head = new TreeNode(nums[0]);

  for (std::size_t i = 1; i < nums.size(); i++) {
    InsertNode(head, new TreeNode(nums[i]));
  }

  PreOrderPrint(head);
  std::cout << std::endl;

  std::string encoded_data = Serialize(head);;
  std::cout << encoded_data << std::endl;

  PreOrderPrint(Deserialize(encoded_data));
  std::cout << std::endl;

  return 0;
}
