#include <iostream>
#include <string>
#include <vector>
#include <list>

// 92. Reverse Linked List II

// Reverse a linked list from position m to n.Do it in - place and in one - pass.
// For example :
// Given 1->2->3->4->5->NULL, m = 2 and n = 4, return 1->4->3->2->5->NULL.
// Note :
//  Given m, n satisfy the following condition : 1 �� m �� n �� length of list.

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

// �������Ϊ���Σ�Ȼ��͵������м�Σ�Ȼ�����ν������ӣ�����Ҫ����ÿ�ε���β�ڵ㡣
// ����֮�����Ǵ�һ���ڵ㿪ʼ���á�
ListNode* ReverseList(ListNode* head, int m, int n) {
  if (head == nullptr) {
    return nullptr;
  }

  if (m <= 0 || m > n) {
    return nullptr;
  }

  ListNode* new_list_head = head;

  // ÿ�������ĳ�ʼ��״̬ʮ����Ҫ��һ��Ҫ��ʼ����ȷ��״̬�������ں�����б�����
  ListNode* before_from_node = nullptr;  // ��ʼ���ýڵ��ǰһ���ڵ㣬��������ڵ㷽���������������ͷ��㡣
  ListNode* current_reverse_node = head;  // ��Ҫ��ʼ���õĽڵ㡣

  // current_reverse_node != nullptr��������ı���������ж�ʮ����Ҫ����ֹ���ʿ�ָ�룬Ҳ���ж������β�ķ�����
  for (int i = 1; i < m && current_reverse_node != nullptr; i++) {
    before_from_node = current_reverse_node;
    current_reverse_node = current_reverse_node->next;
  }

  ListNode* section_list_tail_node = current_reverse_node;  // �����һ����ʼ���õĽڵ㣬���������Ӻ�������
  ListNode* section_list_head_node = nullptr;

  // �ܹ�����to-from+1����㡣
  for (int i = m; i <= n; i++) {
    ListNode* backup_node = current_reverse_node->next;
    current_reverse_node->next = section_list_head_node;
    section_list_head_node = current_reverse_node;
    current_reverse_node = backup_node;
  }

  // ǰ������������м������
  if (m != 1) {
    before_from_node->next = section_list_head_node;
  } else {  // �ӵ�һ���ڵ㿪ʼ���á�
    new_list_head = section_list_head_node;  // ����ӵ�һ���ڵ����ã���ô�м�������ͷ�ͳ���ԭ�������ͷ��
  }

  // �м���������Ӻ�������
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
