#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 23. Merge k Sorted Lists

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 方法一：首先把所有节点放到一个vector中，然后排序，最后链接成链表。很巧妙的方法，且效率很高。
ListNode* mergeKLists1(const std::vector<ListNode*>& lists) {
  std::vector<ListNode*> all_nodes;
  for (ListNode* list : lists) {
    ListNode* head = list;
    while (head != NULL) {
      all_nodes.push_back(head);
      head = head->next;
    }
  }

  std::sort(all_nodes.begin(), all_nodes.end(), [](ListNode* lhs, ListNode* rhs) { return lhs->val < rhs->val; });
  if (all_nodes.empty()) {
    return NULL;
  }

  for (std::size_t i = 0; i < all_nodes.size() - 1; i++) {
    all_nodes[i]->next = all_nodes[i + 1];
  }

  all_nodes.back()->next = NULL;

  return all_nodes[0];
}

//----------------------------------------------------------------------------

// 方法二：采用分治的思想，两两进行Merge，类似于归并排序，将大规模的数据分成小规模的进行处理，
// 最后进行结果合并。

ListNode* MergeTwoLists(ListNode* list1, ListNode* list2) {
  ListNode empty_node(-1);
  ListNode* tail_node = &empty_node;

  while (list1 != NULL && list2 != NULL) {
    ListNode* node = NULL;
    if (list1->val <= list2->val) {
      node = list1;
      list1 = list1->next;
    } else {
      node = list2;
      list2 = list2->next;
    }

    tail_node->next = node;
    node->next = NULL;
    tail_node = tail_node->next;
  }

  if (list1 != NULL) {
    tail_node->next = list1;
  }

  if (list2 != NULL) {
    tail_node->next = list2;
  }

  return empty_node.next;
}

// 递归实现分治。由于递归大量的进行函数进栈出栈操作所以效率明显低于第一种方法。
ListNode* mergeKLists2(const std::vector<ListNode*>& lists) {
  if (lists.empty()) {
    return NULL;
  }

  if (lists.size() == 1) {
    return lists.front();
  }

  if (lists.size() == 2) {
    return MergeTwoLists(lists[0], lists[1]);
  }

  std::size_t mid = lists.size() / 2;

  // 该代码和之前实现的归并排序一样。
  // 将原来的数据从中点分成两部分，然后每部分别递归处理。
  std::vector<ListNode*> lists1;
  for (std::size_t i = 0; i < mid; i++) {
    lists1.push_back(lists[i]);
  }

  std::vector<ListNode*> lists2;
  for (std::size_t i = mid; i < lists.size(); i++) {
    lists2.push_back(lists[i]);
  }

  ListNode* list1 = mergeKLists2(lists1);
  ListNode* list2 = mergeKLists2(lists2);

  return MergeTwoLists(list1, list2);
}

//---------------------------------------------------------------------------

// 方法三：同样采用分治思想，非递归实现，循环实现。效率明显提高，与方法一接近。

ListNode* mergeKLists3(std::vector<ListNode*>& lists) {
  if (lists.empty()) {
    return NULL;
  }

  // 将lists的首尾数据进行合并，合并之后存到首部位置。首尾位置为：i和lists.len()-1-i。
  while (lists.size() > 1) {
    const std::size_t LISTS_LEN = lists.size();

    std::size_t mid = LISTS_LEN / 2;
    for (std::size_t i = 0; i < mid; i++) {
      lists[i] = MergeTwoLists(lists[i], lists[LISTS_LEN - 1 - i]);
    }

    lists.resize((LISTS_LEN + 1) / 2);  // 加一是进一法。例如len为3时，分支合并一次后，len应该为2。
  }

  // 方分治合并到最后，lists就只剩下一个数据。
  return lists.front();
}

//---------------------------------------------------------------------------

void PrintList(ListNode* list) {
  ListNode* node = list;
  while (node != NULL) {
    std::cout << node->val << "->";
    node = node->next;
  }

  std::cout << "NULL" << std::endl;
}

ListNode* CreateList(const std::vector<int>& nums) {
  if (nums.empty()) {
    return NULL;
  }

  ListNode* head = NULL;
  head = new ListNode(nums.front());

  ListNode* pre_node = head;
  for (std::size_t i = 1; i < nums.size(); i++) {
    pre_node->next = new ListNode(nums[i]);
    pre_node = pre_node->next;
  }

  return head;
}

void DestroyList(ListNode** list) {
  ListNode* head = *list;
  if (head == NULL) {
    return;
  }

  std::cout << "Delete node: ";
  while (head != NULL) {
    ListNode* node = head;
    head = head->next;

    std::cout << node->val << " ";
    delete node;
  }

  std::cout << std::endl;

  *list = NULL;
}

void TestCase1() {
  ListNode* list1 = CreateList({ 1, 4, 5 });
  ListNode* list2 = CreateList({ 1, 3, 4 });
  ListNode* list3 = CreateList({ 2, 6 });

  ListNode* merged_list = mergeKLists1({ list1, list2, list3 });
  PrintList(merged_list);

  DestroyList(&merged_list);
}

void TestCase2() {
  ListNode* list1 = CreateList({ 1, 4, 5 });
  ListNode* list2 = CreateList({ 1, 3, 4 });
  ListNode* list3 = CreateList({ 2, 6 });

  ListNode* merged_list = mergeKLists2({ list1, list2, list3 });
  PrintList(merged_list);

  DestroyList(&merged_list);
}

void TestCase3() {
  ListNode* list1 = CreateList({ 1, 4, 5 });
  ListNode* list2 = CreateList({ 1, 3, 4 });
  ListNode* list3 = CreateList({ 2, 6 });

  std::vector<ListNode*> lists{ list1, list2, list3 };

  ListNode* merged_list = mergeKLists3(lists);
  PrintList(merged_list);

  DestroyList(&merged_list);
}

int main() {
  TestCase1();
  std::cout << std::endl;
  TestCase2();
  std::cout << std::endl;
  TestCase3();


  return 0;
}
