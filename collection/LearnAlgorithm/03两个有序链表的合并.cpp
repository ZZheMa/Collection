#include <iostream>
#include <string>
#include <vector>
#include <list>

// 21. Merge Two Sorted Lists

// Merge two sorted linked lists and return it as a new list.
// The new list should be made by splicing together the nodes of the first two lists.
// splice together： 把...拼接在一起。
// the first two lists: 前两个链表。

// Example:
// Input: 1->2->4, 1->3->4
// Output : 1->1->2->3->4->4

struct ListNode {
  int value;
  ListNode* next;

  ListNode(int value_)
    : value(value_)
    , next(nullptr) {
  }
};

void PrintList(ListNode* head) {
  while (head != nullptr) {
    std::cout << head->value;

    head = head->next;
    if (head != nullptr) {
      std::cout << ", ";
    }
  }

  std::cout << std::endl;
}

// ！！！这是一个操作链表的技巧！！！
// 使用一个空的头节点，否则直接使用一个 ListNode* new_list_head = nullptr;
// 会使得初始化状态十分难确定，需要单独判断第一次遍历这一个特殊情况。
// 给链表加一个空的头节点，简化其操作，不用判断操作第一个节点
// 这一特殊情况！链表的插入和删除也能用到这一个技巧。
ListNode* MergeTwoLists(ListNode* list1, ListNode* list2) {
  ListNode empty_head_node(-1);
  ListNode* new_list_tail = &empty_head_node;

  while (list1 != nullptr && list2 != nullptr) {
    if (list1->value > list2->value) {
      new_list_tail->next = list2;
      list2 = list2->next;
    } else {
      new_list_tail->next = list1;
      list1 = list1->next;
    }

    new_list_tail = new_list_tail->next;
  }

  if (list1 != nullptr) {
    new_list_tail->next = list1;
  }

  if (list2 != nullptr) {
    new_list_tail->next = list2;
  }

  return empty_head_node.next;
}


void TestCase1() {
  ListNode node1(1);
  ListNode node3(3);
  ListNode node5(5);
  ListNode node7(7);
  node1.next = &node3;
  node3.next = &node5;
  node5.next = &node7;
  PrintList(&node1);

  ListNode node2(2);
  ListNode node4(4);
  ListNode node6(6);
  node2.next = &node4;
  node4.next = &node6;
  PrintList(&node2);

  // Merge之后，原来的两个链表都遭到了破坏。
  ListNode* new_list = MergeTwoLists(&node1, &node2);

  PrintList(new_list);
}

int main() {
  TestCase1();

  return 0;
}

