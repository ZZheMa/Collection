#include "seq_queue.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "seq_list.h"

SeqQueue* SeqQueue_Create(int capacity) {
  return SeqList_Create(capacity);
}

void SeqQueue_Destroy(SeqQueue* queue) {
  SeqList_Destroy(queue);
}

void SeqQueue_Clear(SeqQueue* queue) {
  SeqList_Clear(queue);
}

int SeqQueue_Append(SeqQueue* queue, void* item) {
  int ret = 0;
  ret = SeqList_Insert(queue, item, SeqList_Length(queue));
  return ret;
}

void* SeqQueue_Retrieve(SeqQueue* queue) {
  SeqListNode* ret = SeqList_Delete(queue, 0);
  return ret;
}

void* SeqQueue_Header(SeqQueue* queue) {
  SeqListNode* node = SeqList_Get(queue, 0);
  return node;
}

int SeqQueue_Length(SeqQueue* queue) {
  return SeqList_Length(queue);
}

int SeqQueue_Capacity(SeqQueue* queue) {
  return SeqList_Capacity(queue);
}
