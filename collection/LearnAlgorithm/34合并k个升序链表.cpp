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

// ����һ�����Ȱ����нڵ�ŵ�һ��vector�У�Ȼ������������ӳ�����������ķ�������Ч�ʺܸߡ�
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

// �����������÷��ε�˼�룬��������Merge�������ڹ鲢���򣬽����ģ�����ݷֳ�С��ģ�Ľ��д���
// �����н���ϲ���

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

// �ݹ�ʵ�ַ��Ρ����ڵݹ�����Ľ��к�����ջ��ջ��������Ч�����Ե��ڵ�һ�ַ�����
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

  // �ô����֮ǰʵ�ֵĹ鲢����һ����
  // ��ԭ�������ݴ��е�ֳ������֣�Ȼ��ÿ���ֱ�ݹ鴦��
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

// ��������ͬ�����÷���˼�룬�ǵݹ�ʵ�֣�ѭ��ʵ�֡�Ч��������ߣ��뷽��һ�ӽ���

ListNode* mergeKLists3(std::vector<ListNode*>& lists) {
  if (lists.empty()) {
    return NULL;
  }

  // ��lists����β���ݽ��кϲ����ϲ�֮��浽�ײ�λ�á���βλ��Ϊ��i��lists.len()-1-i��
  while (lists.size() > 1) {
    const std::size_t LISTS_LEN = lists.size();

    std::size_t mid = LISTS_LEN / 2;
    for (std::size_t i = 0; i < mid; i++) {
      lists[i] = MergeTwoLists(lists[i], lists[LISTS_LEN - 1 - i]);
    }

    lists.resize((LISTS_LEN + 1) / 2);  // ��һ�ǽ�һ��������lenΪ3ʱ����֧�ϲ�һ�κ�lenӦ��Ϊ2��
  }

  // �����κϲ������lists��ֻʣ��һ�����ݡ�
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
