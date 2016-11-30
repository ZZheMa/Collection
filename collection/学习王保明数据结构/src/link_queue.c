#include "link_queue.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_list.h"

typedef struct {
  LinkListNode node;
  void* item;
}TLinkQueueNode;

LinkQueue* LinkQueue_Create() {
  return LinkList_Create();
}

void LinkQueue_Destroy(LinkQueue* queue) {
  LinkQueue_Clear(queue);
  LinkList_Destroy(queue);
}

void LinkQueue_Clear(LinkQueue* queue) {
  while (LinkList_Length(queue) > 0) {
    LinkQueue_Retrieve(queue);
  }
}

int LinkQueue_Append(LinkQueue* queue, void *item) {
  int ret = 0;
  TLinkQueueNode* tnode = (TLinkQueueNode*)malloc(sizeof(TLinkQueueNode));
  if (tnode == NULL) {
    return -1;
  }

  tnode->item = item;
  ret = LinkList_Insert(queue, (LinkListNode*)tnode, LinkList_Length(queue));
  if (ret != 0) {
    free(tnode);
  }

  return ret;
}

void* LinkQueue_Retrieve(LinkQueue* queue) {
  TLinkQueueNode* tnode = (TLinkQueueNode*)LinkList_Delete(queue, 0);
  if (tnode == NULL) {
    return NULL;
  }

  void* item = tnode->item;
  free(tnode);

  return item;
}

void* LinkQueue_Header(LinkQueue* queue) {
  TLinkQueueNode* tnode = (TLinkQueueNode*)LinkList_Get(queue, 0);
  if (tnode == NULL) {
    return NULL;
  }

  return tnode->item;
}

int LinkQueue_Length(LinkQueue* queue) {
  return LinkList_Length(queue);
}
