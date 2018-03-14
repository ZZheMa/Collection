#include <iostream>
#include <string>
#include <map>
#include <list>

// 138. Copy List with Random Pointer

// A linked list is given such that each node contains an additional random pointer
// which could point to any node in the list or null.
// Return a deep copy of the list.

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
  int label;
  RandomListNode* next;
  RandomListNode* random;

  RandomListNode(int x)
      : label(x)
      , next(nullptr)
      , random(nullptr) {
  }
};

void PrintRandomList(RandomListNode* head) {
  while (head != nullptr) {
    std::cout << "label: " << head->label << "; random: ";
    if (head->random == nullptr) {
      std::cout << "NULL";
    } else {
      std::cout << head->random->label;
    }

    std::cout << std::endl;

    head = head->next;
  }
}

RandomListNode* CopyRandomList(RandomListNode *head) {
  RandomListNode* old_list_head = head;

  // 地址对应标号.
  std::map<RandomListNode*, int> old_list_map;

  std::list<RandomListNode*> new_nodes;
  int n = 0;
  while ( head != nullptr) {
    old_list_map[head] = n++;

    RandomListNode* new_node = new RandomListNode(*head);
    new_nodes.push_back(new_node);

    head = head->next;
  }
  old_list_map[nullptr] = n;

  // 标号对应地址。
  std::map<int, RandomListNode*> new_list_map;

  n = 0;
  RandomListNode empty_head_node(-1);
  RandomListNode* temp_node = &empty_head_node;
  for (RandomListNode* new_node : new_nodes) {
    new_list_map[n++] = new_node;

    temp_node->next = new_node;
    temp_node = temp_node->next;
  }

  temp_node->next = nullptr;
  new_list_map[n] = nullptr;

  RandomListNode* new_list_head = empty_head_node.next;
  while (old_list_head != nullptr && new_list_head != nullptr) {
    int n = old_list_map[old_list_head->random];
    new_list_head->random = new_list_map[n];

    old_list_head = old_list_head->next;
    new_list_head = new_list_head->next;
  }

  return empty_head_node.next;
}

void TestCase() {
  RandomListNode node1(1);
  RandomListNode node2(2);
  RandomListNode node3(3);
  RandomListNode node4(4);
  RandomListNode node5(5);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;

  node1.random = nullptr;
  node2.random = &node1;
  node3.random = &node2;
  node4.random = &node3;
  node5.random = &node4;

  PrintRandomList(&node1);

  std::cout << "==============================" << std::endl;

  RandomListNode* new_head = CopyRandomList(&node1);
  PrintRandomList(new_head);

  // Free memory.
  while (new_head != nullptr) {
    RandomListNode* temp_node = new_head;
    new_head = new_head->next;

    delete temp_node;
    temp_node->next = nullptr;
    temp_node->random = nullptr;
  }
}

int main() {
  TestCase();

  return 0;
}
