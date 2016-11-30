#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "seq_list.h"

typedef struct _Teacher {
  int age;
  char* name_;
}Teacher;

void Test1() {
  SeqList* teachers = NULL;
  Teacher t1, t2, t3;
  t1.age = 11;
  t2.age = 12;
  t3.age = 13;

  teachers = SeqList_Create(10);

  SeqList_Insert(teachers, &t3, 0);
  SeqList_Insert(teachers, &t2, 0);
  SeqList_Insert(teachers, &t1, 0);

  //头插法
  //实现了，业务数据 和 链表算法的分离。
  for (size_t i = 0; i < SeqList_Length(teachers); ++i) {
    Teacher* temp = (Teacher*)SeqList_Get(teachers,i);
    printf("%d\n", temp->age);
  }

  printf("----------------------------------------------\n");

  while (SeqList_Length(teachers) != 0) {
    Teacher* temp = (Teacher*)SeqList_Delete(teachers, 0);
    if (temp != NULL) {
      printf("%d\n", temp->age);
    }
  }

  printf("The capacity is %d\n.", SeqList_Capacity(teachers));

  SeqList_Destroy(teachers);

  if (teachers == NULL) {
    printf("list is NULL!");
  }

  teachers = NULL;
}

void Test2() {
  SeqList* teachers = NULL;
  Teacher t1, t2, t3;
  t1.age = 11;
  t2.age = 12;
  t3.age = 13;

  if (SeqList_Create2(&teachers, 10) != 0) {
    return;
  }

  SeqList_Insert(teachers, &t3, 0);
  SeqList_Insert(teachers, &t2, 0);
  SeqList_Insert(teachers, &t1, 0);

  //头插法
  //实现了，业务数据 和 链表算法的分离。
  for (size_t i = 0; i < SeqList_Length(teachers); ++i) {
    Teacher* temp = (Teacher*)SeqList_Get(teachers, i);
    printf("%d\n", temp->age);
  }

  printf("----------------------------------------------\n");

  while (SeqList_Length(teachers) != 0) {
    Teacher* temp = (Teacher*)SeqList_Delete(teachers, 0);
    if (temp != NULL) {
      printf("%d\n", temp->age);
    }
  }

  printf("The capacity is %d\n.", SeqList_Capacity(teachers));

  SeqList_Destroy(teachers);

  if (teachers == NULL) {
    printf("list is NULL!");
  }

  teachers = NULL;
}

int main1() {
  printf("++++++++Test1++++++++++++++++++++++++++\n");
  Test1();
  printf("++++++++Test2++++++++++++++++++++++++++\n");
  Test2();
  return 0;
}
