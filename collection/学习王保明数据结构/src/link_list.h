#ifndef SRC_LINK_LIST_H_
#define SRC_LINK_LIST_H_

typedef void LinkList;
typedef unsigned int size_t;

typedef struct _tag_LinkListNode {
  struct _tag_LinkListNode* next;
}LinkListNode;

LinkList* LinkList_Create();

void LinkList_Destroy(LinkList* list);

void LinkList_Clear(LinkList* list);

size_t LinkList_Length(LinkList* list);

int LinkList_Insert(LinkList* list, LinkListNode* node, size_t pos);

LinkListNode* LinkList_Delete(LinkList* list, size_t pos);

LinkListNode* LinkList_Get(LinkList* list, size_t pos);

#endif  // SRC_LINK_LIST_H_