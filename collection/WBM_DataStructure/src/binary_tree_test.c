#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "binary_tree.h"

void test1() {
  BinaryTreeNode b1, b2, b3, b4, b5;
  memset(&b1, 0, sizeof(BinaryTreeNode));
  memset(&b2, 0, sizeof(BinaryTreeNode));
  memset(&b3, 0, sizeof(BinaryTreeNode));
  memset(&b4, 0, sizeof(BinaryTreeNode));
  memset(&b5, 0, sizeof(BinaryTreeNode));

  b1.data = 0;
  b2.data = 1;
  b3.data = 2;
  b4.data = 3;
  b5.data = 4;

  b1.left_child = &b2;
  b1.right_child = &b3;
  b2.left_child = &b4;
  b2.right_child = &b5;
}

void test2() {
  BinaryTree b1, b2, b3, b4, b5;
  b1 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b2 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b3 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b4 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b5 = (BinaryTree)malloc(sizeof(BinaryTreeNode));

  memset(b1, 0, sizeof(BinaryTreeNode));
  memset(b2, 0, sizeof(BinaryTreeNode));
  memset(b3, 0, sizeof(BinaryTreeNode));
  memset(b4, 0, sizeof(BinaryTreeNode));
  memset(b5, 0, sizeof(BinaryTreeNode));

  b1->data = 0;
  b2->data = 1;
  b3->data = 2;
  b4->data = 3;
  b5->data = 4;

  b1->left_child = b2;
  b1->right_child = b3;
  b2->left_child = b4;
  b2->right_child = b5;

  free(b1);
  free(b2);
  free(b3);
  free(b4);
  free(b5);
}

void test3() {
  BinaryTree b1, b2, b3, b4, b5;
  b1 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b2 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b3 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b4 = (BinaryTree)malloc(sizeof(BinaryTreeNode));
  b5 = (BinaryTree)malloc(sizeof(BinaryTreeNode));

  memset(b1, 0, sizeof(BinaryTreeNode));
  memset(b2, 0, sizeof(BinaryTreeNode));
  memset(b3, 0, sizeof(BinaryTreeNode));
  memset(b4, 0, sizeof(BinaryTreeNode));
  memset(b5, 0, sizeof(BinaryTreeNode));

  b1->data = 0;
  b2->data = 1;
  b3->data = 2;
  b4->data = 3;
  b5->data = 4;

  b1->left_child = b2;
  b1->right_child = b3;
  b2->left_child = b4;
  b2->right_child = b5;

  printf("Previous order traversal.\n");
  PreTraverse(b1);
  printf("\n");

  printf("In order traversal.\n");
  InTraverse(b1);
  printf("\n");

  printf("Post order traversal.\n");
  PostTraverse(b1);
  printf("\n");

  printf("The leaf number is ");
  int num = 0;
  CountLeafNum(b1, &num);
  printf("%d.\n", num);

  printf("The tree depth is ");
  num = GetDepth(b1);
  printf("%d.\n", num);

  BinaryTree new_tree = CopyBinaryTree(b1);
  printf("The new tree's previous order traversal.\n");
  PreTraverse(new_tree);
  printf("\n");

  BinaryTree_Destroy(b1);
  BinaryTree_Destroy(new_tree);

  //free(b1);
  //free(b2);
  //free(b3);
  //free(b4);
  //free(b5);
}

void test4() {
  BinaryTree root = BinaryTree_Create();
  if (root == NULL) {
    return;
  }
  PreTraverse(root);
}

int main5() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
