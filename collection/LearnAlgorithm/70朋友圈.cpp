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

// ���������ж��ٸ���ͨͼ������M����һ���ڽӱ�

// ����һ: ʹ��ͼ��������ȱ�����
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

// ��������ʹ�ò��鼯����ò��뽻�ļ���������

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
