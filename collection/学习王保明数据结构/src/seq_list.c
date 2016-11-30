#include "seq_list.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
  size_t capacity_;
  size_t length_;
  unsigned int* node_;  // 设置为unsigned int的目的是：32位系统，正好可以存放一个指针，
}TSeqList;              // 所以其申请的数据空间用于存放数据的地址，而不是整个数据。
                        // 如果是存放数据，则不能实现数据与数据结构的分离，因为不知道数据的大小。
                        // 这样的顺序存储结构很灵活。这是其实现的巧妙之处!

//--------------------------------------------------------------------------------------

// 该Create的存储方式为：申请一段连续的空间，前面是TSeqList变量自身的空间，后面是node_指向的空间
// 用于存放数据。
SeqList* SeqList_Create(size_t capacity) {
  TSeqList* ret = NULL;
  
  if (capacity == -1) {
    return NULL;
  }

  size_t list_size = sizeof(TSeqList) + sizeof(unsigned int) * capacity;
  ret = (TSeqList*)malloc(list_size);

  if (ret == NULL) {  // malloc申请内存不成功返回NULL，如果是C++的new，则会抛出异常。
    return NULL;
  }

  memset(ret, 0, list_size);

  ret->node_ = (unsigned int*)(ret + 1);  // ret + 1跳过TSeqList变量的空间，后面的空间转化为unsigned int类型。
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

  memset(tseq_list, 0, size);  // 将上面申请的空间赋值为0;

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
  // list = NULL;  // 错误，毫无意义的操作，因为传进来的list是指针变量的副本，给其赋值，只是给副本赋值。
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

  // 判断是否还有空间
  if (capacity <= len) {
    return -2;
  }

  // 判断位置是否正确
  if (pos >= capacity) {
    return -3;
  }

  // 位置容错
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
