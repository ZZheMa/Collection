#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "double_link_list.h"

typedef struct {
  DoubleLinkListNode node;
  int value;
}Value2;

int main13() {
  Value2 v1, v2, v3, v4, v5;
  v1.value = 1;
  v2.value = 2;
  v3.value = 3;
  v4.value = 4;
  v5.value = 5;

  DoubleLinkList* list = DoubleLinkList_Create();
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v1, DoubleLinkList_Length(list));
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v2, DoubleLinkList_Length(list));
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v3, DoubleLinkList_Length(list));
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v4, DoubleLinkList_Length(list));
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v5, DoubleLinkList_Length(list));

  for (int i = 0; i < DoubleLinkList_Length(list); i++) {
    Value2* value = (Value2*)DoubleLinkList_Get(list, i);
    printf("%d ", value->value);
  }
  printf("\n");

  while (DoubleLinkList_Length(list) != 0) {
    Value2* value = (Value2*)DoubleLinkList_Delete(list, 0);
    printf("%d ", value->value);
  }
  printf("\n");

  //---------------------------------------------------------------------------------

  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v1, 0);
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v2, 0);
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v3, 0);
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v4, 0);
  DoubleLinkList_Insert(list, (DoubleLinkListNode*)&v5, 0);

  DoubleLinkList_Reset(list);

  while (DoubleLinkList_IsDone(list) != 0) {
    Value2* value = (Value2*)DoubleLinkList_Next(list);
    printf("%d ", value->value);
  }
  printf("\n");

  DoubleLinkList_Reset(list);
  DoubleLinkList_Next(list);
  DoubleLinkList_Next(list);
  DoubleLinkList_Next(list);
  DoubleLinkList_Next(list);

  while (DoubleLinkList_IsDone(list) != 0) {
    Value2* value = (Value2*)DoubleLinkList_Pre(list);
    printf("%d ", value->value);
  }
  printf("\n");


  DoubleLinkList_Destroy(list);

  return 0;
}
