#include "double_link_list.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
  DoubleLinkListNode header;
  DoubleLinkListNode* slider;
  int length;
}TDoubleLinkList;

DoubleLinkList* DoubleLinkList_Create() {
  TDoubleLinkList* list = (TDoubleLinkList*)malloc(sizeof(TDoubleLinkList));
  if (list == NULL) {
    return NULL;
  }

  list->header.next = NULL;
  list->header.pre = NULL;
  list->slider = NULL;
  list->length = 0;
  return list;
}

void DoubleLinkList_Destroy(DoubleLinkList* list) {
  if (list != NULL) {
    free(list);
  }
}

void DoubleLinkList_Clear(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL) {
    return;
  }

  tlist->header.next = NULL;
  tlist->header.pre = NULL;
  tlist->slider = NULL;
  tlist->length = 0;
}

int DoubleLinkList_Length(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL) {
    return -1;
  }

  return tlist->length;
}

int DoubleLinkList_Insert(DoubleLinkList* list, DoubleLinkListNode* node, int pos) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL) {
    return 1;
  }

  if (node == NULL) {
    return 2;
  }

  if (pos < 0 || pos > tlist->length) {
    return 3;
  }

  DoubleLinkListNode* current = &tlist->header;
  for (int i = 0; i < pos; ++i) {
    current = current->next;
  }

  // 正方向链接。
  DoubleLinkListNode* next = current->next;  // 如果空链表，则next = NULL。
  current->next = node;
  node->next = next;

  // 步骤3-4 
  if (next != NULL) // 当链表插入第一个元素，需要特殊处理
  {
    next->pre = node;
  }
  node->pre = current;

  if (tlist->length == 0) {
    tlist->slider = node; // 当链表插入第一个元素处理游标
  }

  // 若在0位置插入，需要特殊处理 新来结点next前pre指向null
  if (current == (DoubleLinkListNode*)tlist) {
    node->pre = NULL;
  }

  tlist->length++;

  return 0;
}

DoubleLinkListNode* DoubleLinkList_Get(DoubleLinkList* list, int pos) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || pos < 0 || pos >= tlist->length) {
    return NULL;
  }

  DoubleLinkListNode* current = tlist->header.next;
  for (int i = 0; i < pos; ++i) {
    current = current->next;
  }

  return current;
}

DoubleLinkListNode* DoubleLinkList_Delete(DoubleLinkList* list, int pos) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || pos < 0 || pos >= tlist->length || tlist->length == 0) {
    return NULL;
  }

  DoubleLinkListNode* current = &tlist->header;
  for (int i = 0; i < pos; ++i) {
    current = current->next;
  }

  DoubleLinkListNode* ret = current->next;
  DoubleLinkListNode* next = ret->next;
  current->next = next;  // 如果只有一个元素，next.next = NULL。

  if (next == NULL) {
    tlist->slider = NULL;
  } else {
    next->pre = current;  // 如果是删除第一个元素，那么current指向的是头节点。
    if (tlist->slider == ret) {
      tlist->slider = next;
    }
    if (current == (DoubleLinkListNode*)list) {
      next->pre = NULL;
    }
  }

  tlist->length--;

  return ret;
}

DoubleLinkListNode* DoubleLinkList_DeleteNode(DoubleLinkList* list, DoubleLinkListNode* node) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || node == NULL) {
    return NULL;
  }

  DoubleLinkListNode* current = &tlist->header;
  for (int i = 0; i < tlist->length; ++i) {
    current = current->next;
    if (current == node) {
      return DoubleLinkList_Delete(list, i);
    }
  }

  return NULL;
}

DoubleLinkListNode* DoubleLinkList_Reset(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL) {
    return NULL;
  }

  tlist->slider = tlist->header.next;
  return tlist->slider;
}

DoubleLinkListNode* DoubleLinkList_Current(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || tlist->slider == NULL) {
    return NULL;
  }

  return tlist->slider;
}

DoubleLinkListNode* DoubleLinkList_Next(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || tlist->slider == NULL) {
    return NULL;
  }

  DoubleLinkListNode* ret = tlist->slider;
  tlist->slider = ret->next;
  return ret;
}

DoubleLinkListNode* DoubleLinkList_Pre(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || tlist->slider == NULL) {
    return NULL;
  }

  DoubleLinkListNode* ret = tlist->slider;
  tlist->slider = ret->pre;
  return ret;
}

int DoubleLinkList_IsDone(DoubleLinkList* list) {
  TDoubleLinkList* tlist = (TDoubleLinkList*)list;
  if (tlist == NULL || tlist->slider == NULL) {
    return 0;
  }
  return 1;
}