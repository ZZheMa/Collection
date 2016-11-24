#include "circle_list.h"
#include <stdlib.h>
#include <string.h>

// 循环链表，思想和链表的思想类似，只是插入删除可能由于循环的原因，有点特别。

typedef struct {
  CircleListNode header;  // 头节点。
  CircleListNode* slider;  // 游标，访问使用,类似一个迭代器进行遍历。
  int length;  // 链表长度。
}TCircleList;

CircleList* CircleList_Create() {
  TCircleList* tlist = (TCircleList*)malloc(sizeof(TCircleList));
  if (tlist == NULL) {
    return NULL;
  }

  tlist->header.next = NULL;
  tlist->slider = NULL;
  tlist->length = 0;

  return tlist;
}

void CircleList_Destroy(CircleList* list) {
  if (list == NULL) {
    return;
  }

  free(list);
}

void CircleList_Clear(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL) {
    return;
  }

  tlist->header.next = NULL;
  tlist->slider = NULL;
  tlist->length = 0;
}

int CircleList_Length(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL) {
    return -1;
  }

  return tlist->length;
}

CircleListNode* CircleList_Get(CircleList* list, int pos) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL || pos < 0) {
    return NULL;
  }

  CircleListNode* current = tlist->header.next;
  for (int i = 0; i < pos; ++i) {
    current = current->next;
  }

  return current;
}

int CircleList_Insert(CircleList* list, CircleListNode* node, int pos) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL) {
    return -1;
  }

  if (node == NULL) {
    return -2;
  }

  if (pos < 0) {
    return -3;
  }

  //CircleListNode* current = (CircleListNode*)sList;  // The same effect with the following statement.
  CircleListNode* current = &tlist->header;
  for (int i = 0; i < pos && current->next != NULL; ++i) {  // current->next != NULL这句话是处理length等于零时，pos为非零值。
    current = current->next;
  }

  node->next = current->next;
  current->next = node;

  if (tlist->length == 0) {  // 如果第一次插入节点，则初始化slider。
    tlist->slider = node;
  }

  tlist->length++;

  // 如果是在头部插入，则令最后一个节点指向第一个节点。这个判断也解决了第一次插入节点，如何形成循环的问题。
  // 头节点位置插入和别的情况是不一样的，头节点插入时current是指向头节点的，然后current.next指向node。
  // node变成了位置为0的节点，而该链表的最后一个节点指向的还是原来位置为0的节点。
  // 头插法和其他位置插入的最大区别就是其他位置是断开链表进行插入，而头部是没有断开链表的。
  if (current == (CircleListNode*)tlist) {  // 等价于current == &tlist->header,判断current是否指向头节点，也就是在位置0处插入。
    CircleListNode* last_node = CircleList_Get(list, tlist->length - 1);
    last_node->next = current->next;
  }

  return 0;
}

CircleListNode * CircleList_Delete(CircleList* list, int pos) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL || pos < 0 || tlist->length <= 0) {
    return NULL;
  }

  CircleListNode* current = (CircleListNode*)tlist;
  for (int i = 0; i < pos && current->next != NULL; ++i) {
    current = current->next;
  }

  CircleListNode* ret = current->next;
  current->next = ret->next;
  tlist->length--;

  // 如果删除的是头结点
  CircleListNode* last_node = NULL;
  if (current == (CircleListNode*)tlist) {
    last_node = CircleList_Get(list, tlist->length - 1);
    if (last_node != NULL) {
      last_node = ret->next;
    }
  }

  // 如果删除的是slider指向的位置
  if (tlist->slider == ret) {
    tlist->slider = ret->next;
  }

  if (tlist->length == 0) {
    tlist->header.next = NULL;
    tlist->slider = NULL;
  }

  return ret;
}

CircleListNode* CircleList_DeleteNode(CircleList* list, CircleListNode* node) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  CircleListNode* current = &tlist->header;
  for (int i = 0; i < tlist->length; i++) {
    current = current->next;
    if (current = node) {
      return CircleList_Delete(list, i);
    }
  }

  return NULL;
}

CircleListNode* CircleList_Reset(CircleList * list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  tlist->slider = tlist->header.next;
  return tlist->slider;
}

CircleListNode* CircleList_Current(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  return tlist->slider;
}

CircleListNode* CircleList_Next(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  tlist->slider = tlist->slider->next;
  return tlist->slider;
}
