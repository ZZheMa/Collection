#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 547. Friend Circles

// 本质是求有多少个连通图。变量M就是一个邻接表。

// 方法一: 使用图的深度优先遍历。
int findCircleNum1(const std::vector<std::vector<int>>& M) {
  if (M.empty()) {
    return 0;
  }

  const std::size_t COUNT = M.size();

  std::vector<int> visit(COUNT, 0);

  std::function<void(int)> dfs;
  dfs = [&M, &visit, &dfs, COUNT](int node) {
    visit[node] = 1;

    for (std::size_t i = 0; i < COUNT; ++i) {
      if (visit[i] != 1 && M[node][i] == 1) {
        dfs(i);
      }
    }
  };

  int circle_num = 0;
  for (std::size_t i = 0; i < COUNT; ++i) {
    if (visit[i] == 0) {
      ++circle_num;
      dfs(i);
    }
  }

  return circle_num;
}

//-------------------------------------------------

// 方法二：使用并查集来求得不想交的集合数量。

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

int findCircleNum2(const std::vector<std::vector<int>>& M) {
  if (M.empty()) {
    return 0;
  }

  const std::size_t COUNT = M.size();

  DisjointSet disjoint_set(COUNT);
  for (std::size_t i = 0; i < COUNT; ++i) {
    for (std::size_t j = 0; j < COUNT; ++j) {
      if (M[i][j] == 1) {
        disjoint_set.Union(i, j);
      }
    }
  }

  return disjoint_set.set_count();
}

//--------------------------------------------------

int main() {
  std::vector<std::vector<int>> m1 = {
    {1, 1, 0},
    {1, 1, 0},
    {0, 0, 1},
  };

  std::vector<std::vector<int>> m2 = {
    {1, 1, 0},
    {1, 1, 1},
    {0, 1, 1},
  };

  std::cout << findCircleNum1(m1) << std::endl;
  std::cout << findCircleNum1(m2) << std::endl;

  std::cout << findCircleNum2(m1) << std::endl;
  std::cout << findCircleNum2(m2) << std::endl;

  return 0;
}
