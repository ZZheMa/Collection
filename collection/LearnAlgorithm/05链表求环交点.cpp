#include <iostream>
#include <string>
#include <list>
#include <set>
#include <cassert>

// 142. Linked List Cycle II

// Given a linked list, return the node where the cycle begins.If there is no cycle, return null.
// Note: Do not modify the linked list.

// Follow up :
// Can you solve it without using extra space ?

struct ListNode {
  int value;
  ListNode* next;

  ListNode(int val)
    : value(val)
    , next(nullptr) {
  }
};

ListNode* DetectCycle1(ListNode* list) {
  std::set<ListNode*> node_set;
  while (list != nullptr) {
    if (node_set.find(list) != node_set.end()) {
      return list;
    }

    node_set.insert(list);
    list = list->next;
  }

  return nullptr;
}

// ����ָ�뷨��
// ��ָ����ƶ��ٶ�����ָ���ƶ��ٶȵ���������������ʱ���߹���·��Ҳ����ָ���������
ListNode* DetectCycle2(ListNode* list) {
  ListNode* meet_head = nullptr;
  ListNode* low_head = list;
  ListNode* fast_head = list;

  while (low_head != nullptr && fast_head != nullptr) {
    low_head = low_head->next;
    fast_head = fast_head->next;

    if (fast_head != nullptr) {
      fast_head = fast_head->next;
    }

    // ����ָ��ͬʱ�ƶ��������㡣
    if (low_head == fast_head) {
      meet_head = low_head;
      break;
    }
  }

  // Ѱ�һ�����㡣
  while (meet_head != nullptr) {
    if (list == meet_head) {
      return list;
    }

    list = list->next;
    meet_head = meet_head->next;
  }

  return nullptr;
}

void TestCase() {
  ListNode node1(1);
  ListNode node2(2);
  ListNode node3(3);
  ListNode node4(4);
  ListNode node5(5);
  ListNode node6(6);
  ListNode node7(7);
  ListNode node8(8);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;
  node5.next = &node6;
  node6.next = &node7;
  node7.next = &node8;
  node8.next = &node4;

  std::cout << DetectCycle1(&node1)->value << std::endl;
  std::cout << DetectCycle2(&node1)->value << std::endl;
}

int main() {
  TestCase();

  return 0;
}
