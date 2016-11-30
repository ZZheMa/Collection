#include "link_stack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_list.h"

// ��LinkListģ��LinkStack��Ҳ���ǽ�LinkList���з�װ��TlinkStackNode��ʵ���൱��
// Teacher��

typedef struct {
  LinkListNode node;  // ռλ�ṹ������һ�����������ÿ������
  void* item;  // itemΪʵ������
}TLinkStackNode;

LinkStack* LinkStack_Create() {
  return LinkList_Create();
}

void LinkStack_Destroy(LinkStack* stack) {
  LinkStack_Clear(stack);
  LinkList_Destroy(stack);
}

void LinkStack_Clear(LinkStack* stack) {
  while (LinkList_Length(stack) > 0) {
    LinkStack_Pop(stack);
  }
}

int LinkStack_Push(LinkStack* stack, void* item) {
  int ret = 0;
  TLinkStackNode* tnode = (TLinkStackNode*)malloc(sizeof(TLinkStackNode));
  if (tnode == NULL) {
    return -1;
  }

  tnode->item = item;
  // ͷ�巨��
  ret = LinkList_Insert(stack, (LinkListNode*)tnode, 0);
  if (ret != 0) {
    free(tnode);
  }

  return ret;
}

void* LinkStack_Pop(LinkStack* stack) {
  TLinkStackNode* tnode = (TLinkStackNode*)LinkList_Delete(stack, 0);
  if (tnode == NULL) {
    return NULL;
  }

  void* item = tnode->item;
  free(tnode);

  return item;
}

void* LinkStack_Top(LinkStack* stack) {
  TLinkStackNode* tnode = (TLinkStackNode*)LinkList_Get(stack, 0);
  if (tnode == NULL) {
    return NULL;
  }

  return tnode->item;
}

int LinkStack_Size(LinkStack* stack) {
  return LinkList_Length(stack);
}
