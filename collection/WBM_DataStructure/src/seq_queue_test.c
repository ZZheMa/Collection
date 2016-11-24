#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "seq_queue.h"

int main312() {
  int a[100] = {0};
  for (int i = 0; i < 10; i++) {
    a[i] = i;
  }

  SeqQueue* queue = SeqQueue_Create(10);
  for (int i = 0; i < 10; i++) {
    SeqQueue_Append(queue, &a[i]);
  }

  int* tem = (int*)SeqQueue_Header(queue);
  printf("%d\n", *tem);

  for (int i = 0; i < 10; i++) {
    int* tem = (int*)SeqQueue_Retrieve(queue);
    printf("%d ", *tem);
  }
  printf("\n");

  SeqQueue_Destroy(queue);

  return 0;
}
