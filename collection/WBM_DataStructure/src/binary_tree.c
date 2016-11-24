#include "binary_tree.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PreTraverse(BinaryTree root) {
  if (root == NULL) {
    return;
  }

  printf("%d ", root->data);
  PreTraverse(root->left_child);
  PreTraverse(root->right_child);
}

void InTraverse(BinaryTree root) {
  if (root == NULL) {
    return;
  }

  InTraverse(root->left_child);
  printf("%d ", root->data);
  InTraverse(root->right_child);
}

void PostTraverse(BinaryTree root) {
  if (root == NULL) {
    return;
  }

  PostTraverse(root->left_child);
  PostTraverse(root->right_child);
  printf("%d ", root->data);
}

// 实际上就是二叉树遍历的应用。

void CountLeafNum(BinaryTree root, int* num) {
  if (root == NULL) {
    return;
  }

  if (root->left_child == NULL && root->right_child == NULL) {
    (*num)++;
  }
  CountLeafNum(root->left_child, num);
  CountLeafNum(root->right_child, num);
}

int GetDepth(BinaryTree root) {
  int left_depth = 0;
  int right_depth = 0;
  int depth = 0;

  if (root == NULL) {
    depth = 0;
    return depth;
  }

  left_depth = GetDepth(root->left_child);
  right_depth = GetDepth(root->right_child);

  depth = left_depth > right_depth ? left_depth : right_depth;
  depth++;

  return depth;
}

BinaryTree CopyBinaryTree(BinaryTree root) {
  BinaryTree new_root = NULL;
  BinaryTree ltree = NULL;
  BinaryTree rtree = NULL;

  if (root->left_child == NULL) {
    ltree = NULL;
  } else {
    ltree = CopyBinaryTree(root->left_child);
  }

  if (root->right_child == NULL) {
    rtree = NULL;
  } else {
    rtree = CopyBinaryTree(root->right_child);
  }

  new_root = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  if (new_root == NULL) {
    return NULL;
  }

  new_root->left_child = ltree;
  new_root->right_child = rtree;
  new_root->data = root->data;

  return new_root;
}

BinaryTree BinaryTree_Create() {
  BinaryTreeNode* node = NULL;
  char data = 0;

  printf("Node data: ");
  scanf_s("%c", &data);
  fflush(stdin);
  if (data == '#') {
    node = NULL;
    return node;
  } else {
    node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->data = data - '0';
    node->left_child = BinaryTree_Create();
    node->right_child = BinaryTree_Create();
    return node;
  }
}

void BinaryTree_Destroy(BinaryTree root) {
  if (root != NULL) {
    if (root->left_child != NULL) {
      BinaryTree_Destroy(root->left_child);
    }

    if (root->right_child != NULL) {
      BinaryTree_Destroy(root->right_child);
    }

    free(root);
    root = NULL;
  }
}
