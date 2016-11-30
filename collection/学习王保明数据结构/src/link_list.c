#include "link_list.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
  LinkListNode header;
  size_t length;
}TLinkList;

// �������ʵ��˼����������е�ʵ�ֲ���ܴ����ַ����������
// ������ֻmalloc��һ��TlinkLisk�������ýṹ����������������
// ����������Ϣ��һ��������ĳ��ȣ���һ�����������ͷ�ڵ㡣ע�����
// ͷ�ڵ���ָ�룬��ôʹ�õ�ʱ����ҪΪͷ�ڵ��ָ������ڴ���䡣
// �����ͷ�ڵ㣬��ͷ�ڵ���ָ��������LinkListNode�ڵ㣬ÿ���ڵ㶼��
// ����ҵ��ڵ�����ڴ����ģ����Բ��ø�������ж�����ڴ��ͷš�

// ����������һ���ߴ����飬ÿ��ҵ��ڵ�������������ϣ�����Ҫ����һ���������������ϡ�

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
  //list = NULL;  // ���ò�����listΪ������
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

  if (tlist == NULL || pos >= tlist->length) {  // || tlist->header.next == NULLû�б�Ҫ��pos >= tlist->length�Ѿ����������������
    return NULL;
  }

  LinkListNode* current = tlist->header.next;
  for (size_t i = 0; i < pos && current != NULL; ++i) {
    current = current->next;
  }

  return current;
}
