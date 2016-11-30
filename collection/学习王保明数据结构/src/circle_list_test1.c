#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "circle_list.h"

typedef struct {
  CircleListNode circlenode;
  int v;
}Value;

void Test11() {
  CircleList* list = CircleList_Create();

  Value v1;
  Value v2;
  Value v3;
  Value v4;

  int i = 0;

  v1.v = 1;
  v2.v = 2;
  v3.v = 3;
  v4.v = 4;

  CircleList_Insert(list, (CircleListNode*)&v1, 0);
  CircleList_Insert(list, (CircleListNode*)&v2, 0);
  CircleList_Insert(list, (CircleListNode*)&v3, 0);
  CircleList_Insert(list, (CircleListNode*)&v4, 0);

  for (i = 0; i < 2 * CircleList_Length(list); i++) {
    Value* pv = (Value*)CircleList_Get(list, i);

    printf("%d\n", pv->v);
  }

  while (CircleList_Length(list) > 0) {
    CircleList_Delete(list, 0);
  }

  printf("\n");

  CircleList_Destroy(list);
}

// 约瑟夫环。
void Test12() {
  int i = 0;
  CircleList* list = CircleList_Create();


  Value v1, v2, v3, v4, v5, v6, v7, v8;

  v1.v = 1;	v2.v = 2;	v3.v = 3;	v4.v = 4;
  v5.v = 5;	v6.v = 6;	v7.v = 7;	v8.v = 8;

  CircleList_Insert(list, (CircleListNode*)&v1, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v2, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v3, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v4, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v5, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v6, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v7, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v8, CircleList_Length(list));


  for (i = 0; i < CircleList_Length(list); i++) {
    Value* pv = (Value*)CircleList_Next(list);
    printf("%d\n", pv->v);
  }

  printf("\n");

  CircleList_Reset(list);

  while (CircleList_Length(list) > 0) {
    Value* pv = NULL;
    for (i = 1; i < 3; i++) {  // 从2开始数，数到2时跳出。
      CircleList_Next(list);
    }
    pv = (Value*)CircleList_Current(list);
    printf("%d\n", pv->v);
    CircleList_DeleteNode(list, (CircleListNode*)pv);
  }

  CircleList_Destroy(list);
}

void Test13() {
  int i = 0;
  CircleList* list = CircleList_Create();

  Value v1;
  Value v2;
  Value v3;
  Value v4;
  Value v5;
  Value v6;
  Value v7;
  Value v8;

  v1.v = 1;
  v2.v = 2;
  v3.v = 3;
  v4.v = 4;
  v5.v = 5;
  v6.v = 6;
  v7.v = 7;
  v8.v = 8;

  CircleList_Insert(list, (CircleListNode*)&v1, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v2, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v3, CircleList_Length(list));
  CircleList_Insert(list, (CircleListNode*)&v4, CircleList_Length(list));

  //CircleList_Insert(list, (CircleListNode*)&v5, 5);
  //CircleList_Delete(list, 0);

  for (i = 0; i < 2 * CircleList_Length(list); i++) {
    Value* pv = (Value*)CircleList_Get(list, i);
    printf("%d\n", pv->v);
  }

  printf("\n");

  while (CircleList_Length(list) > 0) {
    Value* pv = (Value*)CircleList_Delete(list, 0);

    printf("%d\n", pv->v);
  }

  printf("\n");
 
  printf("\n");

  CircleList_Reset(list);

  while (CircleList_Length(list) > 0) {
    Value* pv = NULL;

    for (i = 1; i < 3; i++) {
      CircleList_Next(list);
    }

    pv = (Value*)CircleList_Current(list);

    printf("%d\n", pv->v);

    CircleList_DeleteNode(list, (CircleListNode*)pv);
  }

  CircleList_Destroy(list);
}

int main4(int argc, char *argv[]) {
  //Test1();
  //Test12();
  Test13();
  return 0;
}