#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_list.h"

typedef struct {  // ÿ��ҵ��ڵ㶼����һ������ڵ㣬ͨ��������ڵ��������е�ҵ��ڵ����ӡ�
  LinkListNode node;  // Teacher�ĵ�ַ�Ǻ͸�node�ĵ�ַ�ص��ģ����Կ��Խ�������ַ���ͽ��л���ת����

  char name[256];
  int age;
}Teacher;


int main3() {
  Teacher t1, t2, t3;
  t1.age = 11;
  t2.age = 12;
  t3.age = 13;

  LinkList* list = LinkList_Create();

  // ʵ��ҵ��ڵ���㷨�ķ��롣
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
