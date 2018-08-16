#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 线段树

// 将一个数组二分为多个区间，每个区间的加和存放到二叉树的某个结点里面。
// 这个二叉树是一个完全二叉树，用数组来保存这个二叉树，标号从0开始。
// 第i个结点的左结点和右结点分别为2*i+1和2*i+2 。

// 根节点存放整个区间的加和，其左结点存放左半区间的加和，其右结点存放右半区间的加和。

class SegmentTree {
public:
  SegmentTree(const std::vector<int>& nums)
      : nums_(nums)
      , tree_array_(nums.size() * 4, 0) {
  }

  void Build() {
    if (nums_.empty()) {
      return;
    }

    Build(0, 0, nums_.size() - 1);
  }

  int Sum(std::size_t begin, std::size_t end) const {
    if (nums_.empty()) {
      return 0;
    }

    int sum = 0;
    Sum(0, 0, nums_.size() - 1, begin, end, sum);
    return sum;
  }

  void Update(std::size_t tree_pos,
              std::size_t nums_begin,
              std::size_t nums_end,
              std::size_t index,
              int value) {
    if (nums_begin > nums_end) {
      return;
    }

    if (nums_begin == nums_end) {
      if (nums_begin == index) {
        tree_array_[index] = value;
      }
      return;
    }

    std::size_t left_child_node_pos = 2 * tree_pos + 1;
    std::size_t right_child_node_pos = 2 * tree_pos + 2;

    std::size_t nums_mid = (nums_end + nums_begin) / 2;

    if (index <= nums_mid) {
      Build(left_child_node_pos, nums_begin, nums_mid);
    } else {
      Build(right_child_node_pos, nums_mid + 1, nums_end);
    }

    tree_array_[tree_pos] = tree_array_[left_child_node_pos] + tree_array_[right_child_node_pos];
  }

  void Update(std::size_t index, int value) {
    if (nums_.empty()) {
      return;
    }

    if (index >= nums_.size()) {
      return;
    }

    nums_[index] = value;
    Update(0, 0, nums_.size() - 1, index, value);
  }

  void Print() const {
    if (nums_.empty()) {
      return;
    }

    PreOrderPrint(0, 0, nums_.size() - 1);
  }

private:
  // tree_pos,nums_begin,nums_end这三个变量成组出现，treee_array[tree_pos]表示给定数组
  // [nums_begin, nums_end]这一区间的加和。
  void Build(std::size_t tree_pos, std::size_t nums_begin, std::size_t nums_end) {
    if (nums_begin > nums_end) {
      return;
    }

    // nums_begin == nums_end说明当前结点是叶子结点。
    if (nums_begin == nums_end) {
      tree_array_[tree_pos] = nums_[nums_begin];
      return;
    }

    std::size_t left_child_node_pos = 2 * tree_pos + 1;
    std::size_t right_child_node_pos = 2 * tree_pos + 2;

    std::size_t nums_mid = (nums_end + nums_begin) / 2;

    // 建立左子树。
    Build(left_child_node_pos, nums_begin, nums_mid);
    // 建立右子树。
    Build(right_child_node_pos, nums_mid + 1, nums_end);

    tree_array_[tree_pos] = tree_array_[left_child_node_pos] + tree_array_[right_child_node_pos];
  }

  void PreOrderPrint(std::size_t tree_pos, std::size_t nums_begin, std::size_t nums_end) const {
    std::cout << "[" << nums_begin << ", " << nums_end << "] : " << tree_array_[tree_pos] << std::endl;

    if (nums_begin >= nums_end) {
      return;
    }

    std::size_t left_child_node_pos = 2 * tree_pos + 1;
    std::size_t right_child_node_pos = 2 * tree_pos + 2;

    std::size_t nums_mid = (nums_end + nums_begin) / 2;

    PreOrderPrint(left_child_node_pos, nums_begin, nums_mid);
    PreOrderPrint(right_child_node_pos, nums_mid + 1, nums_end);
  }

  void Sum(std::size_t tree_pos,
           std::size_t nums_begin,
           std::size_t nums_end,
           std::size_t begin,
           std::size_t end,
           int& sum) const {
    // 如果带求区间不在nums的区间的范围，则直接返回。
    if (begin > nums_end || end < nums_begin) {
      return;
    }

    // 如果nums的区间在带求区间内，则该区间的加和tree_array_[tree_pos]是带求区间的一个分量。
    if (begin <= nums_begin && end >= nums_end) {
      sum += tree_array_[tree_pos];
      return;
    }

    std::size_t left_child_node_pos = 2 * tree_pos + 1;
    std::size_t right_child_node_pos = 2 * tree_pos + 2;

    std::size_t nums_mid = (nums_end + nums_begin) / 2;
    Sum(left_child_node_pos, nums_begin, nums_mid, begin, end, sum);
    Sum(right_child_node_pos, nums_mid + 1, nums_end, begin, end, sum);
  }

private:
  // nums 表示给定数组。
  std::vector<int> nums_;

  // tree_array表示存放该二叉树的数组。
  std::vector<int> tree_array_;

  // tree_array_[0]表示根结点，也就是整个给定数组的加和。
};

int main() {
  SegmentTree segment_tree({ 1, 2, 3, 4, 5 });
  segment_tree.Build();
  segment_tree.Print();
  std::cout << segment_tree.Sum(2, 3) << std::endl;
  std::cout << segment_tree.Sum(2, 4) << std::endl;
  std::cout << segment_tree.Sum(1, 4) << std::endl;

  segment_tree.Update(4, 10);
  std::cout << segment_tree.Sum(3, 4) << std::endl;
  std::cout << segment_tree.Sum(2, 4) << std::endl;

  return 0;
}
