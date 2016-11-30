#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int a;
}Node1;

typedef struct {
  Node1 node;
  int b;
}Node2;

int main2() {
  Node2 node;
  printf("%d\n", &node.node);  // node.node 的地址和node的地址重叠。
  printf("%d\n", &node);
  printf("%d\n", &node.b);

  printf("%d\n", sizeof(node));
  printf("%d\n", sizeof(node.node));
  printf("%d\n", sizeof(Node2));
  printf("%d\n", sizeof(Node1));

  return 0;
}
