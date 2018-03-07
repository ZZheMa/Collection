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

// 1.就地逆置法: 从旧链表的头结点开始，一个节点一个节点的向后逆置。（没有额外空间的申请。）
ListNode* ReverseList(ListNode* head) {
  ListNode* new_head = NULL;  // 逆置后链表的头结点。初始化新链表为NULL。

  // head就是当前要逆置的节点。 如果当前的节点为NULL则不用逆置。
  while (head != NULL) {
    ListNode* backup_node = head->next;  // 备份当前要逆置节点后面的节点。
    head->next = new_head;  // 逆置当前节点。
    new_head = head;  // new链表的头结点指向当前逆置的节点。
    head = backup_node;  // head指向下一个需要逆置的节点。
  }

  return new_head;
}

// 2.头插法: 与就地逆置法原理一样。区别是就地逆置法的新链表用一个指针来指向，头插法的新链表加了一个临时的
// 头结点。所以每次逆置的结点都插入到头结点后面，所以叫头插法。（但是需要申请额外的空间。）
ListNode* ReverseList2(ListNode* head) {
  ListNode temp_head_node(-1);

  while (head != NULL) {  // 与就地逆置法一样一个一个结点的进行逆置，如果当前结点为NULL则不用进行逆置了。
    ListNode* backup_node = head->next;  // 备份后面的链表。
    head->next = temp_head_node.next;  // 当前逆置的结点插入到temp_head_node后面。
    temp_head_node.next = head;
    head = backup_node;  // head指向下一个需要逆置的结点。
  }

  return temp_head_node.next;  // 头结点的next指向新的链表。
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
