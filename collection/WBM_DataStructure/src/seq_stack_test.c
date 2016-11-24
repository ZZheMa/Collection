#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "seq_stack.h"

int main14() {
  int value[20];
  SeqStack* stack = SeqStack_Create(20);

  for (int i = 0; i < 10; i++) {
    value[i] = i * 5;
    SeqStack_Push(stack, &value[i]);
  }

  printf("capacity : %d\n", SeqStack_Capacity(stack));
  printf("length : %d\n", SeqStack_Size(stack));
  printf("top : %d\n", *(int*)SeqStack_Top(stack));

  for (int i = 0; i < 10; i++) {
    printf("%d ", *(int*)SeqStack_Pop(stack));
  }
  printf("\n");

  SeqStack_Destroy(stack);
  return 0;
}
