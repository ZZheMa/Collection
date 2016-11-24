#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_list.h"

typedef struct {  // 每个业务节点都保存一个链表节点，通过该链表节点来将所有的业务节点连接。
  LinkListNode node;  // Teacher的地址是和该node的地址重叠的，所以可以将两个地址类型进行互相转换。

  char name[256];
  int age;
}Teacher;


int main3() {
  Teacher t1, t2, t3;
  t1.age = 11;
  t2.age = 12;
  t3.age = 13;

  LinkList* list = LinkList_Create();

  // 实现业务节点和算法的分离。
  LinkList_Insert(list, (LinkListNode*)&t1, LinkList_Length(list));
  LinkList_Insert(list, (LinkListNode*)&t2, LinkList_Length(list));
  LinkList_Insert(list, (LinkListNode*)&t3, LinkList_Length(list));

  for (size_t i = 0; i < LinkList_Length(list); ++i) {
    Teacher* teacher = (Teacher*)LinkList_Get(list, i);
    if (teacher != NULL) {
      printf("%d\n", teacher->age);
    }
  }

  printf("------------------------------------------\n");

  while (LinkList_Length(list) != 0) {
    Teacher* teacher = (Teacher*)LinkList_Delete(list, LinkList_Length(list) - 1);
    if (teacher != NULL) {
      printf("%d\n", teacher->age);
    }
  }

  LinkList_Destroy(list);
  list = NULL;

  return 0;
}
