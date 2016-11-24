#ifndef SRC_BINARY_TREE_H_
#define SRC_BINARY_TREE_H_

typedef struct _tag_BinaryTreeNode{
  int data;
  struct _tag_BinaryTreeNode* left_child;
  struct _tag_BinaryTreeNode* right_child;
}BinaryTreeNode, *BinaryTree;

// ǰ�����
void PreTraverse(BinaryTree root);

// �������
void InTraverse(BinaryTree root);

// �������
void PostTraverse(BinaryTree root);

// ��Ҷ�ӽڵ���
void CountLeafNum(BinaryTree root, int* num);

// ���������
int GetDepth(BinaryTree root);

// ������
BinaryTree CopyBinaryTree(BinaryTree root);

// # ������
BinaryTree BinaryTree_Create();

// ������
void BinaryTree_Destroy(BinaryTree root);

#endif  // SRC_BINARY_TREE_H_
