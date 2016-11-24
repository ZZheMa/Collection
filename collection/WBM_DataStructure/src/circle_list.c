#include "circle_list.h"
#include <stdlib.h>
#include <string.h>

// ѭ������˼��������˼�����ƣ�ֻ�ǲ���ɾ����������ѭ����ԭ���е��ر�

typedef struct {
  CircleListNode header;  // ͷ�ڵ㡣
  CircleListNode* slider;  // �α꣬����ʹ��,����һ�����������б�����
  int length;  // �����ȡ�
}TCircleList;

CircleList* CircleList_Create() {
  TCircleList* tlist = (TCircleList*)malloc(sizeof(TCircleList));
  if (tlist == NULL) {
    return NULL;
  }

  tlist->header.next = NULL;
  tlist->slider = NULL;
  tlist->length = 0;

  return tlist;
}

void CircleList_Destroy(CircleList* list) {
  if (list == NULL) {
    return;
  }

  free(list);
}

void CircleList_Clear(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL) {
    return;
  }

  tlist->header.next = NULL;
  tlist->slider = NULL;
  tlist->length = 0;
}

int CircleList_Length(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL) {
    return -1;
  }

  return tlist->length;
}

CircleListNode* CircleList_Get(CircleList* list, int pos) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL || pos < 0) {
    return NULL;
  }

  CircleListNode* current = tlist->header.next;
  for (int i = 0; i < pos; ++i) {
    current = current->next;
  }

  return current;
}

int CircleList_Insert(CircleList* list, CircleListNode* node, int pos) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL) {
    return -1;
  }

  if (node == NULL) {
    return -2;
  }

  if (pos < 0) {
    return -3;
  }

  //CircleListNode* current = (CircleListNode*)sList;  // The same effect with the following statement.
  CircleListNode* current = &tlist->header;
  for (int i = 0; i < pos && current->next != NULL; ++i) {  // current->next != NULL��仰�Ǵ���length������ʱ��posΪ����ֵ��
    current = current->next;
  }

  node->next = current->next;
  current->next = node;

  if (tlist->length == 0) {  // �����һ�β���ڵ㣬���ʼ��slider��
    tlist->slider = node;
  }

  tlist->length++;

  // �������ͷ�����룬�������һ���ڵ�ָ���һ���ڵ㡣����ж�Ҳ����˵�һ�β���ڵ㣬����γ�ѭ�������⡣
  // ͷ�ڵ�λ�ò���ͱ������ǲ�һ���ģ�ͷ�ڵ����ʱcurrent��ָ��ͷ�ڵ�ģ�Ȼ��current.nextָ��node��
  // node�����λ��Ϊ0�Ľڵ㣬������������һ���ڵ�ָ��Ļ���ԭ��λ��Ϊ0�Ľڵ㡣
  // ͷ�巨������λ�ò������������������λ���ǶϿ�������в��룬��ͷ����û�жϿ�����ġ�
  if (current == (CircleListNode*)tlist) {  // �ȼ���current == &tlist->header,�ж�current�Ƿ�ָ��ͷ�ڵ㣬Ҳ������λ��0�����롣
    CircleListNode* last_node = CircleList_Get(list, tlist->length - 1);
    last_node->next = current->next;
  }

  return 0;
}

CircleListNode * CircleList_Delete(CircleList* list, int pos) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL || pos < 0 || tlist->length <= 0) {
    return NULL;
  }

  CircleListNode* current = (CircleListNode*)tlist;
  for (int i = 0; i < pos && current->next != NULL; ++i) {
    current = current->next;
  }

  CircleListNode* ret = current->next;
  current->next = ret->next;
  tlist->length--;

  // ���ɾ������ͷ���
  CircleListNode* last_node = NULL;
  if (current == (CircleListNode*)tlist) {
    last_node = CircleList_Get(list, tlist->length - 1);
    if (last_node != NULL) {
      last_node = ret->next;
    }
  }

  // ���ɾ������sliderָ���λ��
  if (tlist->slider == ret) {
    tlist->slider = ret->next;
  }

  if (tlist->length == 0) {
    tlist->header.next = NULL;
    tlist->slider = NULL;
  }

  return ret;
}

CircleListNode* CircleList_DeleteNode(CircleList* list, CircleListNode* node) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  CircleListNode* current = &tlist->header;
  for (int i = 0; i < tlist->length; i++) {
    current = current->next;
    if (current = node) {
      return CircleList_Delete(list, i);
    }
  }

  return NULL;
}

CircleListNode* CircleList_Reset(CircleList * list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  tlist->slider = tlist->header.next;
  return tlist->slider;
}

CircleListNode* CircleList_Current(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  return tlist->slider;
}

CircleListNode* CircleList_Next(CircleList* list) {
  TCircleList* tlist = (TCircleList*)list;
  if (tlist == NULL && tlist->slider == NULL) {
    return NULL;
  }

  tlist->slider = tlist->slider->next;
  return tlist->slider;
}
