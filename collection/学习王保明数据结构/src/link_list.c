#include "link_list.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
  LinkListNode header;
  size_t length;
}TLinkList;

// 该链表的实现思想和其他书中的实现差异很大，这种方法更加巧妙。
// 该链表只malloc了一个TlinkLisk变量，该结构体变量存了这个链表
// 的两部分信息，一个事链表的长度，另一个就是链表的头节点。注意如果
// 头节点用指针，那么使用的时候还需要为头节点的指针进行内存分配。
// 存放了头节点，用头节点来指向其他的LinkListNode节点，每个节点都是
// 外面业务节点进行内存分配的，所以不用该链表进行对其的内存释放。

// 这个链表就像一根线穿佛珠，每个业务节点如果想连在线上，就需要保存一个佛珠来套在线上。

LinkList* LinkList_Create() {
  TLinkList* tlist = (TLinkList*)malloc(sizeof(TLinkList));
  if (tlist == NULL) {
    return NULL;
  }

  tlist->header.next = NULL;
  tlist->length = 0;

  return tlist;
}

void LinkList_Destroy(LinkList * list) {
  if (list == NULL) {
    return;
  }

  free(list);
  //list = NULL;  // 无用操作，list为副本。
}

void LinkList_Clear(LinkList * list) {
  TLinkList* tlist = (TLinkList*)list;

  if (tlist == NULL) {
    return;
  }

  tlist->header.next = NULL;
  tlist->length = 0;
}

size_t LinkList_Length(LinkList * list) {
  TLinkList* tlist = (TLinkList*)list;

  if (tlist == NULL) {
    return -1;
  }

  return tlist->length;
}

int LinkList_Insert(LinkList * list, LinkListNode * node, size_t pos) {
  if (node == NULL) {
    return 1;
  }

  TLinkList* tlist = (TLinkList*)list;
  if (tlist == NULL) {
    return 2;
  }

  if (pos > tlist->length) {
    return 3;
  }

  LinkListNode* current = &tlist->header;
  for (size_t i = 0; i < pos && current != NULL; ++i) {
    current = current->next;
  }
  node->next = current->next;
  current->next = node;
  tlist->length++;

  return 0;
}

LinkListNode * LinkList_Delete(LinkList * list, size_t pos) {
  TLinkList* tlist = (TLinkList*)list;

  if (tlist == NULL || pos >= tlist->length) {
    return NULL;
  }

  LinkListNode* current = &tlist->header;
  for (size_t i = 0; i < pos && current->next != NULL; ++i) {
    current = current->next;
  }

  LinkListNode* ret = current->next;
  current->next = ret->next;
  tlist->length--;

  return ret;
}

LinkListNode * LinkList_Get(LinkList * list, size_t pos) {
  TLinkList* tlist = (TLinkList*)list;

  if (tlist == NULL || pos >= tlist->length) {  // || tlist->header.next == NULL没有必要，pos >= tlist->length已经包含了这种情况。
    return NULL;
  }

  LinkListNode* current = tlist->header.next;
  for (size_t i = 0; i < pos && current != NULL; ++i) {
    current = current->next;
  }

  return current;
}
