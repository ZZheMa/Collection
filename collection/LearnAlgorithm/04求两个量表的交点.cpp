#include <iostream>
#include <string>
#include <list>
#include <set>
#include <cassert>

// 160. Intersection of Two Linked Lists

// Write a program to find the node at which the intersection of two singly linked lists begins.

// Notes :
// If the two linked lists have no intersection at all, return null.
// The linked lists must retain their original structure after the function returns.
// You may assume there are no cycles anywhere in the entire linked structure.
// Your code should preferably run in O(n) time and use only O(1) memory.

struct ListNode {
  int value;
  ListNode* next;

  ListNode(int val)
      : value(val)
      , next(nullptr) {
  }
};

ListNode* GetIntersectionNode1(ListNode* list1, ListNode* list2) {
  while (list1 != nullptr) {
    ListNode* head = list2;
    while (head != nullptr) {
      if (list1 == head) {
        return head;
      }

      head = head->next;
    }

    list1 = list1->next;
  }

  return nullptr;
}

ListNode* GetIntersectionNode2(ListNode* list1, ListNode* list2) {
  std::set<ListNode*> node_set1;
  while (list1 != nullptr) {
    node_set1.insert(list1);
    list1 = list1->next;
  }

  while (list2 != nullptr) {
    if (node_set1.find(list2) != node_set1.end()) {
      return list2;
    }

    list2 = list2->next;
  }

  return nullptr;
}

// 求出两条链表的长度，然后将初始指针进行位置对其，然后同时移动，直到相遇。
ListNode* GetIntersectionNode3(ListNode* list1, ListNode* list2) {
  auto get_list_length = [](ListNode* list) {
    int length = 0;
    while (list != nullptr) {
      ++length;
      list = list->next;
    }

    return length;
  };

  int list1_len = get_list_length(list1);
  int list2_len = get_list_length(list2);

  auto forward_nodes = [](ListNode* list, int n) {
    while (list != nullptr && n != 0) {
      list = list->next;
      --n;
    }

    return list;
  };

  if (list1_len > list2_len) {
    list1 = forward_nodes(list1, list1_len - list2_len);
  } else {
    list2 = forward_nodes(list2, list2_len - list1_len);
  }

  while (list1 != nullptr && list2 != nullptr) {
    if (list1 == list2) {
      return list1;
    }

    list1 = list1->next;
    list2 = list2->next;
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

  node7.next = &node8;
  node8.next = &node5;

  std::cout << GetIntersectionNode1(&node1, &node7)->value << std::endl;
  std::cout << GetIntersectionNode2(&node1, &node7)->value << std::endl;
  std::cout << GetIntersectionNode3(&node1, &node7)->value << std::endl;
}

int main() {
  TestCase();

  return 0;
}
