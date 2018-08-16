#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// �߶���

// ��һ���������Ϊ������䣬ÿ������ļӺʹ�ŵ���������ĳ��������档
// �����������һ����ȫ���������������������������������Ŵ�0��ʼ��
// ��i������������ҽ��ֱ�Ϊ2*i+1��2*i+2 ��

// ���ڵ�����������ļӺͣ����������������ļӺͣ����ҽ�����Ұ�����ļӺ͡�

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
  // tree_pos,nums_begin,nums_end����������������֣�treee_array[tree_pos]��ʾ��������
  // [nums_begin, nums_end]��һ����ļӺ͡�
  void Build(std::size_t tree_pos, std::size_t nums_begin, std::size_t nums_end) {
    if (nums_begin > nums_end) {
      return;
    }

    // nums_begin == nums_end˵����ǰ�����Ҷ�ӽ�㡣
    if (nums_begin == nums_end) {
      tree_array_[tree_pos] = nums_[nums_begin];
      return;
    }

    std::size_t left_child_node_pos = 2 * tree_pos + 1;
    std::size_t right_child_node_pos = 2 * tree_pos + 2;

    std::size_t nums_mid = (nums_end + nums_begin) / 2;

    // ������������
    Build(left_child_node_pos, nums_begin, nums_mid);
    // ������������
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
    // ����������䲻��nums������ķ�Χ����ֱ�ӷ��ء�
    if (begin > nums_end || end < nums_begin) {
      return;
    }

    // ���nums�������ڴ��������ڣ��������ļӺ�tree_array_[tree_pos]�Ǵ��������һ��������
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
  // nums ��ʾ�������顣
  std::vector<int> nums_;

  // tree_array��ʾ��Ÿö����������顣
  std::vector<int> tree_array_;

  // tree_array_[0]��ʾ����㣬Ҳ����������������ļӺ͡�
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
