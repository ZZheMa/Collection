#include <iostream>
#include <string>
#include <list>
#include <cassert>

// 86. Partition List

// Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
// You should preserve the original relative order of the nodes in each of the two partitions.

// For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.

struct ListNode {
  int value;
  ListNode* next;

  ListNode(int val)
    : value(val)
    , next(nullptr) {
  }
};

void PrintList(ListNode* list) {
  while (list != nullptr) {
    std::cout << list->value << ", ";
    list = list->next;
  }

  std::cout << std::endl;
}

// ������ʱ�յ�ͷ��㡣
// ˼·����С��x�Ľ��ƴ�ӳ�һ�����������ڵ���x�Ľ��ƴ�ӳ���һ��������������������ӡ�
ListNode* Partition(ListNode* head, int x) {
  ListNode less_list_head(-1);
  ListNode* less_list_node = &less_list_head;

  ListNode more_list_head(-1);
  ListNode* more_list_node = &more_list_head;

  while (head != nullptr) {
    if (head->value < x) {
      less_list_node->next = head;
      less_list_node = head;
    } else {
      more_list_node->next = head;
      more_list_node = head;
    }

    head = head->next;
  }

  less_list_node->next = more_list_head.next;
  more_list_node->next = nullptr;  // ע�⴦�����һ����㡣

  return less_list_head.next;
}

void TestCase() {
  ListNode node1(1);
  ListNode node2(4);
  ListNode node3(3);
  ListNode node4(4);
  ListNode node5(2);
  ListNode node6(6);
  ListNode node7(9);
  ListNode node8(7);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;
  node5.next = &node6;
  node6.next = &node7;
  node7.next = &node8;

  PrintList(&node1);
  ListNode* new_head = Partition(&node1, 4);
  PrintList(new_head);
}

int main() {
  TestCase();

  return 0;
}
