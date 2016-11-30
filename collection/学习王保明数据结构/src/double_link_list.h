#ifndef SRC_DOUBLE_LINK_LIST_H_
#define SRC_DOUBLE_LINK_LIST_H_

typedef void DoubleLinkList;

typedef struct _tag_DoubleLinkListNode {
  struct _tag_DoubleLinkListNode* next;
  struct _tag_DoubleLinkListNode* pre;
}DoubleLinkListNode;

DoubleLinkList* DoubleLinkList_Create();

void DoubleLinkList_Destroy(DoubleLinkList* list);

void DoubleLinkList_Clear(DoubleLinkList* list);

int DoubleLinkList_Length(DoubleLinkList* list);

int DoubleLinkList_Insert(DoubleLinkList* list, DoubleLinkListNode* node, int pos);

DoubleLinkListNode* DoubleLinkList_Get(DoubleLinkList* list, int pos);

DoubleLinkListNode* DoubleLinkList_Delete(DoubleLinkList* list, int pos);

DoubleLinkListNode* DoubleLinkList_DeleteNode(DoubleLinkList* list, DoubleLinkListNode* node);

DoubleLinkListNode* DoubleLinkList_Reset(DoubleLinkList* list);

DoubleLinkListNode* DoubleLinkList_Current(DoubleLinkList* list);

DoubleLinkListNode* DoubleLinkList_Next(DoubleLinkList* list);

DoubleLinkListNode* DoubleLinkList_Pre(DoubleLinkList* list);

int DoubleLinkList_IsDone(DoubleLinkList* list);

#endif  // SRC_DOUBLE_LINK_LIST_H_
