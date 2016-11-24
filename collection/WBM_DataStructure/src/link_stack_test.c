#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_stack.h"

int main111() {
  int a[100] = {0};
  for (int i = 0; i < 10; i++) {
    a[i] = i;
  }

  LinkStack* stack = LinkStack_Create();
  for (int i = 0; i < 10; i++) {
    LinkStack_Push(stack, &a[i]);
  }

  int* tem = (int*)LinkStack_Top(stack);
  printf("%d\n", *tem);

  for (int i = 0; i < 10; i++) {
    int* tem = (int*)LinkStack_Pop(stack);
    printf("%d ", *tem);
  }
  printf("\n");

  return 0;
}
