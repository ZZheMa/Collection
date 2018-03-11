#include <iostream>
#include <string>
#include <vector>
#include <list>

// 92. Reverse Linked List II

// Reverse a linked list from position m to n.Do it in - place and in one - pass.
// For example :
// Given 1->2->3->4->5->NULL, m = 2 and n = 4, return 1->4->3->2->5->NULL.
// Note :
//  Given m, n satisfy the following condition : 1 ≤ m ≤ n ≤ length of list.

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

// 将链表分为三段，然后就地逆置中间段，然后将三段进行连接，所以要保存每段的首尾节点。
// 特殊之处就是从一个节点开始逆置。
ListNode* ReverseList(ListNode* head, int m, int n) {
  if (head == nullptr) {
    return nullptr;
  }

  if (m <= 0 || m > n) {
    return nullptr;
  }

  ListNode* new_list_head = head;

  // 每个变量的初始化状态十分重要，一定要初始化正确的状态，才能在后面进行遍历。
  ListNode* before_from_node = nullptr;  // 开始逆置节点的前一个节点，保存这个节点方便其连接新链表的头结点。
  ListNode* current_reverse_node = head;  // 将要开始逆置的节点。

  // current_reverse_node != nullptr对于链表的遍历，这个判断十分重要！防止访问空指针，也是判断链表结尾的方法。
  for (int i = 1; i < m && current_reverse_node != nullptr; i++) {
    before_from_node = current_reverse_node;
    current_reverse_node = current_reverse_node->next;
  }

  ListNode* section_list_tail_node = current_reverse_node;  // 保存第一个开始逆置的节点，方便其连接后半段链表。
  ListNode* section_list_head_node = nullptr;

  // 总共逆置to-from+1个结点。
  for (int i = m; i <= n; i++) {
    ListNode* backup_node = current_reverse_node->next;
    current_reverse_node->next = section_list_head_node;
    section_list_head_node = current_reverse_node;
    current_reverse_node = backup_node;
  }

  // 前半段链表连接中间段链表。
  if (m != 1) {
    before_from_node->next = section_list_head_node;
  } else {  // 从第一个节点开始逆置。
    new_list_head = section_list_head_node;  // 如果从第一个节点逆置，那么中间段链表的头就成了原来链表的头。
  }

  // 中间段链表连接后半段链表。
  section_list_tail_node->next = current_reverse_node;

  return new_list_head;
}

void TestCase1() {
  ListNode n1(1);
  ListNode n2(4);
  ListNode n3(3);
  ListNode n4(2);
  ListNode n5(5);

  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  n4.next = &n5;

  PrintList(&n1);
  ListNode* new_head1 = ReverseList(&n1, 2, 4);
  PrintList(new_head1);

  ListNode* new_head2 = ReverseList(&n1, 1, 5);
  PrintList(new_head2);
}

void TestCase2() {
  ListNode* new_head = ReverseList(nullptr, 1, 2);
  if (new_head == nullptr) {
    std::cout << "Case2 pass" << std::endl;
  }
}

int main() {
  TestCase1();
  TestCase2();
  
  return 0;
}
