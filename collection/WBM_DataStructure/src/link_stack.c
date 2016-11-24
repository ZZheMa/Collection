#include "link_stack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_list.h"

// 用LinkList模拟LinkStack，也就是将LinkList进行封装，TlinkStackNode其实就相当于
// Teacher。

typedef struct {
  LinkListNode node;  // 占位结构，就是一条链子上面的每个环。
  void* item;  // item为实际数据
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
  // 头插法。
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
