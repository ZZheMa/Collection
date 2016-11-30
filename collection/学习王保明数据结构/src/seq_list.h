#ifndef SRC_SEQ_LIST_H_
#define SRC_SEQ_LIST_H_

typedef unsigned int size_t;

// ���Ա��˳��洢�ṹ��

// Ҫʵ�����ݽṹ��ҵ��ķ��롣

typedef void SeqListNode;  // ��������Ϊvoid�����κβ��������Խ��գ�Ҳ����ʵ����ҵ�������ݽṹ�ķ��롣
typedef void SeqList;

int SeqList_Create2(SeqList** list, size_t capacity);

SeqList* SeqList_Create(size_t capacity);

size_t SeqList_Length(SeqList* list);

size_t SeqList_Capacity(SeqList* list);

void SeqList_Destroy(SeqList* list);

void SeqList_Clear(SeqList* list);

SeqListNode* SeqList_Get(SeqList* list, size_t pos);

SeqListNode* SeqList_Delete(SeqList* list, size_t pos);

int SeqList_Insert(SeqList* list, SeqListNode* node, size_t pos);

#endif  // SRC_SEQ_LIST_H_
