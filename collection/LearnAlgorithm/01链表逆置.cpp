#include <iostream>
#include <string>
#include <vector>
#include <list>

struct ListNode {
  int value;
  ListNode* next;

  ListNode(int val)
      : value(val)
      , next(NULL) {
  }
};

void PrintList(ListNode* head) {
  while (head != NULL) {
    std::cout << head->value;
    head = head->next;

    if (head != NULL) {
      std::cout << ", ";
    }
  }

  std::cout << std::endl;
}

// 1.�͵����÷�: �Ӿ������ͷ��㿪ʼ��һ���ڵ�һ���ڵ��������á���û�ж���ռ�����롣��
ListNode* ReverseList(ListNode* head) {
  ListNode* new_head = NULL;  // ���ú������ͷ��㡣��ʼ��������ΪNULL��

  // head���ǵ�ǰҪ���õĽڵ㡣 �����ǰ�Ľڵ�ΪNULL�������á�
  while (head != NULL) {
    ListNode* backup_node = head->next;  // ���ݵ�ǰҪ���ýڵ����Ľڵ㡣
    head->next = new_head;  // ���õ�ǰ�ڵ㡣
    new_head = head;  // new�����ͷ���ָ��ǰ���õĽڵ㡣
    head = backup_node;  // headָ����һ����Ҫ���õĽڵ㡣
  }

  return new_head;
}

// 2.ͷ�巨: ��͵����÷�ԭ��һ���������Ǿ͵����÷�����������һ��ָ����ָ��ͷ�巨�����������һ����ʱ��
// ͷ��㡣����ÿ�����õĽ�㶼���뵽ͷ�����棬���Խ�ͷ�巨����������Ҫ�������Ŀռ䡣��
ListNode* ReverseList2(ListNode* head) {
  ListNode temp_head_node(-1);

  while (head != NULL) {  // ��͵����÷�һ��һ��һ�����Ľ������ã������ǰ���ΪNULL���ý��������ˡ�
    ListNode* backup_node = head->next;  // ���ݺ��������
    head->next = temp_head_node.next;  // ��ǰ���õĽ����뵽temp_head_node���档
    temp_head_node.next = head;
    head = backup_node;  // headָ����һ����Ҫ���õĽ�㡣
  }

  return temp_head_node.next;  // ͷ����nextָ���µ�����
}

int main() {
  ListNode a(1);
  ListNode b(2);
  ListNode c(3);
  ListNode d(4);
  ListNode e(5);

  ListNode* head = &a;
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;

  PrintList(head);
  ListNode* new_list_head = ReverseList(head);
  PrintList(new_list_head);

  ListNode* new_list_head2 = ReverseList2(new_list_head);
  PrintList(new_list_head2);

  return 0;
}
