#ifndef SRC_BINARY_TREE_H_
#define SRC_BINARY_TREE_H_

typedef struct _tag_BinaryTreeNode{
  int data;
  struct _tag_BinaryTreeNode* left_child;
  struct _tag_BinaryTreeNode* right_child;
}BinaryTreeNode, *BinaryTree;

// 前序遍历
void PreTraverse(BinaryTree root);

// 中序遍历
void InTraverse(BinaryTree root);

// 后序遍历
void PostTraverse(BinaryTree root);

// 求叶子节点数
void CountLeafNum(BinaryTree root, int* num);

// 求树的深度
int GetDepth(BinaryTree root);

// 拷贝树
BinaryTree CopyBinaryTree(BinaryTree root);

// # 创建树
BinaryTree BinaryTree_Create();

// 销毁树
void BinaryTree_Destroy(BinaryTree root);

#endif  // SRC_BINARY_TREE_H_
