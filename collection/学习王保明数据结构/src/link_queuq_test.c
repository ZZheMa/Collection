#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_queue.h"

int main213() {
  int a[100] = { 0 };
  for (int i = 0; i < 10; i++) {
    a[i] = i;
  }

  LinkQueue* queue = LinkQueue_Create();
  for (int i = 0; i < 10; i++) {
    LinkQueue_Append(queue, &a[i]);
  }

  int* tem = (int*)LinkQueue_Header(queue);
  printf("%d\n", *tem);

  for (int i = 0; i < 10; i++) {
    int* tem = (int*)LinkQueue_Retrieve(queue);
    printf("%d ", *tem);
  }
  printf("\n");

  return 0;
}
