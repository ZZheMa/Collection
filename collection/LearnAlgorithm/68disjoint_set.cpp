#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 并查集

// 可以判断两个元素是否有交集。

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

    // 合并的时候将规模小的树指向规模的的树的根结点。
    if (set_sizes_[i_root] > set_sizes_[j_root]) {
      set_sizes_[i_root] += set_sizes_[j_root];
      nodes_[j_root] = i_root;
    } else {
      set_sizes_[j_root] += set_sizes_[i_root];
      nodes_[i_root] = j_root;
    }

    --set_count_;
  }

  // 在查找的时候进行路并压缩，使当前的结点指向父结点的父结点。
  // 路径压缩使得所有结点都直接指向了父结点，提高了查找效率。
  int Find(int i) {
    int parent = nodes_[i];

    // 当前结点的父结点等于当前结点父结点的父结点，那么当前结点恰好指向了根结点。
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
  // 数组的下标代表结点的值，数组的内容代表该结点的父结点。即nodes[i]是i的父结点。
  std::vector<int> nodes_;

  // 结点i的子节点个数。
  std::vector<int> set_sizes_;

  // 不想交集合的数量。
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
