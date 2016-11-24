#include "seq_list.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
  size_t capacity_;
  size_t length_;
  unsigned int* node_;  // ����Ϊunsigned int��Ŀ���ǣ�32λϵͳ�����ÿ��Դ��һ��ָ�룬
}TSeqList;              // ��������������ݿռ����ڴ�����ݵĵ�ַ���������������ݡ�
                        // ����Ǵ�����ݣ�����ʵ�����������ݽṹ�ķ��룬��Ϊ��֪�����ݵĴ�С��
                        // ������˳��洢�ṹ����������ʵ�ֵ�����֮��!

//--------------------------------------------------------------------------------------

// ��Create�Ĵ洢��ʽΪ������һ�������Ŀռ䣬ǰ����TSeqList��������Ŀռ䣬������node_ָ��Ŀռ�
// ���ڴ�����ݡ�
SeqList* SeqList_Create(size_t capacity) {
  TSeqList* ret = NULL;
  
  if (capacity == -1) {
    return NULL;
  }

  size_t list_size = sizeof(TSeqList) + sizeof(unsigned int) * capacity;
  ret = (TSeqList*)malloc(list_size);

  if (ret == NULL) {  // malloc�����ڴ治�ɹ�����NULL�������C++��new������׳��쳣��
    return NULL;
  }

  memset(ret, 0, list_size);

  ret->node_ = (unsigned int*)(ret + 1);  // ret + 1����TSeqList�����Ŀռ䣬����Ŀռ�ת��Ϊunsigned int���͡�
  ret->capacity_ = capacity;
  ret->length_ = 0;

  return ret;
}

int SeqList_Create2(SeqList** list, size_t capacity) {
  if (list == NULL) {
    return 1;
  }

  if (capacity == -1) {
    *list = NULL;
    return 2;
  }

  TSeqList* tseq_list = NULL;
  size_t size = sizeof(TSeqList) + sizeof(unsigned int) * capacity;

  tseq_list = (TSeqList*)malloc(size);

  if (tseq_list == NULL) {
    *list = NULL;
    return 3;
  }

  memset(tseq_list, 0, size);  // ����������Ŀռ丳ֵΪ0;

  tseq_list->node_ = (unsigned int*)(tseq_list + 1);
  tseq_list->capacity_ = capacity;
  tseq_list->length_ = 0;

  *list = tseq_list;

  return 0;
}


size_t SeqList_Length(SeqList* list) {
  if (list == NULL) {
    return -1;
  }

  TSeqList* tseq_list = (TSeqList*)list;
  return tseq_list->length_;
}

size_t SeqList_Capacity(SeqList* list) {
  if (list == NULL) {
    return -1;
  }

  TSeqList* tseq_list = (TSeqList*)list;
  return tseq_list->capacity_;
}

void SeqList_Destroy(SeqList* list) {
  if (list == NULL) {
    return;
  }

  free(list);
  // list = NULL;  // ���󣬺�������Ĳ�������Ϊ��������list��ָ������ĸ��������丳ֵ��ֻ�Ǹ�������ֵ��
}

void SeqList_Clear(SeqList* list) {
  if (list == NULL) {
    return;
  }

  TSeqList* tseq_list = (TSeqList*)list;
  tseq_list->length_ = 0;
}

SeqListNode* SeqList_Get(SeqList* list, size_t pos) {
  TSeqList* tseq_list = (TSeqList*)list;

  if (list == NULL || tseq_list->length_ <= pos) {
    return NULL;
  }

  SeqListNode* ret = (SeqListNode*)tseq_list->node_[pos];

  return ret;
}

SeqListNode* SeqList_Delete(SeqList* list, size_t pos) {
  TSeqList* tseq_list = (TSeqList*)list;

  if (list == NULL || pos >= tseq_list->length_) {
    return NULL;
  }

  SeqListNode* ret = (SeqListNode*)tseq_list->node_[pos];

  for (size_t i = pos; i < tseq_list->length_ - 1; ++i) {
    tseq_list->node_[i] = tseq_list->node_[i + 1];
  }
  tseq_list->length_--;

  return ret;
}

int SeqList_Insert(SeqList* list, SeqListNode* node, size_t pos) {
  if (list == NULL || node == NULL) {
    return -1;
  }

  TSeqList* tseq_list = (TSeqList*)list;
  size_t len = tseq_list->length_;
  size_t capacity = tseq_list->capacity_;

  // �ж��Ƿ��пռ�
  if (capacity <= len) {
    return -2;
  }

  // �ж�λ���Ƿ���ȷ
  if (pos >= capacity) {
    return -3;
  }

  // λ���ݴ�
  if (pos > len) {
    pos = len;
  }

  for (size_t i = len; i > pos; --i) {
    tseq_list->node_[i] = tseq_list->node_[i - 1];
  }
  tseq_list->node_[pos] = (unsigned int)node;
  tseq_list->length_++;

  return 0;
}
