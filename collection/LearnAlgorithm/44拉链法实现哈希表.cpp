#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 使用拉链法实现哈希表。

struct ListNode {
  int value;
  ListNode* next;

  ListNode(int val) : value(val), next(nullptr) {}
};

// 整数取余作为哈希函数。
int HashFunc(int key, int table_len) {
  return key % table_len;
}

void Insert(ListNode* hash_table[], ListNode* node, int table_len) {
  int hash_address = HashFunc(node->value, table_len);

  ListNode* backup_node = hash_table[hash_address];
  hash_table[hash_address] = node;
  node->next = backup_node;
}

bool Search(ListNode* hash_table[], int key, int table_len) {
  int hash_address = HashFunc(key, table_len);

  ListNode* node = hash_table[hash_address];
  while (node != nullptr) {
    if (node->value == key) {
      return true;
    }
    node = node->next;
  }

  return false;
}

void FreeList(ListNode** list) {
  ListNode* head = *list;

  while (head != nullptr) {
    ListNode* backup_node = head->next;
    delete head;
    head = backup_node;
  }

  *list = nullptr;
}

int main() {
  const int kHashTableLen = 11;

  // 哈希表一块连续的内存，查找时，可以直接通过索引进行定位。
  ListNode* hash_table[kHashTableLen] = { nullptr };

  for (auto num : { 3, 5, 199, 2, 43, 16 }) {
    Insert(hash_table, new ListNode(num), kHashTableLen);
  }

  std::cout << Search(hash_table, 3, kHashTableLen) << std::endl;
  std::cout << Search(hash_table, 199, kHashTableLen) << std::endl;
  std::cout << Search(hash_table, 1999, kHashTableLen) << std::endl;

  for (int i = 0; i < kHashTableLen; i++) {
    std::cout << "Address " << i << " : ";
    ListNode* node = hash_table[i];
    while (node != nullptr) {
      std::cout << "->" << node->value;
      node = node->next;
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < kHashTableLen; i++) {
    ListNode* node = hash_table[i];
    FreeList(&node);
  }

  return 0;
}
