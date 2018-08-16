#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// ���鼯

// �����ж�����Ԫ���Ƿ��н�����

class DisjointSet {
public:
  DisjointSet(int n)
      : set_count_(n)
      , set_sizes_(n, 1) {
    for (int i = 0; i < n; ++i) {
      nodes_.push_back(i);
    }
  }

  int set_count() const {
    return set_count_;
  }

  void Union(int i, int j) {
    int i_root = Find(i);
    int j_root = Find(j);

    if (i_root == j_root) {
      return;
    }

    // �ϲ���ʱ�򽫹�ģС����ָ���ģ�ĵ����ĸ���㡣
    if (set_sizes_[i_root] > set_sizes_[j_root]) {
      set_sizes_[i_root] += set_sizes_[j_root];
      nodes_[j_root] = i_root;
    } else {
      set_sizes_[j_root] += set_sizes_[i_root];
      nodes_[i_root] = j_root;
    }

    --set_count_;
  }

  // �ڲ��ҵ�ʱ�����·��ѹ����ʹ��ǰ�Ľ��ָ�򸸽��ĸ���㡣
  // ·��ѹ��ʹ�����н�㶼ֱ��ָ���˸���㣬����˲���Ч�ʡ�
  int Find(int i) {
    int parent = nodes_[i];

    // ��ǰ���ĸ������ڵ�ǰ��㸸���ĸ���㣬��ô��ǰ���ǡ��ָ���˸���㡣
    while (nodes_[parent] != parent) {
      nodes_[i] = nodes_[parent];
      parent = nodes_[i];
    }

    return parent;
  }

  void PrintNodes() const {
    std::cout << "Nodes : ";
    for (std::size_t i = 0; i < nodes_.size(); ++i) {
      std::cout << i << "  ";
    }

    std::cout << std::endl;

    std::cout << "Parent: ";
    for (std::size_t i = 0; i < nodes_.size(); ++i) {
      std::cout << nodes_[i] << "  ";
    }

    std::cout << std::endl;
  }

private:
  // ������±�������ֵ����������ݴ���ý��ĸ���㡣��nodes[i]��i�ĸ���㡣
  std::vector<int> nodes_;

  // ���i���ӽڵ������
  std::vector<int> set_sizes_;

  // ���뽻���ϵ�������
  int set_count_;
};

int main() {
  DisjointSet disjoint_set(10);
  disjoint_set.Union(1, 2);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(3, 4);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(2, 3);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(5, 6);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(6, 7);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(7, 8);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(8, 9);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  disjoint_set.Union(3, 8);
  std::cout << disjoint_set.set_count() << std::endl;
  disjoint_set.PrintNodes();

  std::cout << disjoint_set.Find(3) << std::endl;

  return 0;
}
