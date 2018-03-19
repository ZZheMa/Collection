#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>

// 295. Find Median from Data Stream。

// 巧用最大堆和最小堆。
// 将这组数据分为两段，前半段和后半段，后半段的最小值肯定大于前半段的最大值。
// 所以前半段用最大堆，后半段用最小堆。由于堆的性质可以不用每次都将所有数据都排序，
// 所以极大地提高了效率。
class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {
  }

  void addNum(int num) {
    // 前半段和后半段的长度的差值永远小于等于1。
    std::size_t max_heap_size = max_heap_.size();
    std::size_t min_heap_size = min_heap_.size();

    // 如果前半段长度大于后半段，那么就将一个值放到后半段。
    if (max_heap_size > min_heap_size) {
      // 如果前半段的最大值大于要插入的值，那么该插入的值不能放到后半段。
      // 因为后半段的值肯定大于前半段的值，所以将其交换再放到后半段。
      if (max_heap_.top() > num) {
        min_heap_.push(max_heap_.top());
        max_heap_.pop();
        max_heap_.push(num);
      } else {
        min_heap_.push(num);
      }
    // 如果后半段长度大于前半段，那么就将一个值放到前半段。
    } else if (max_heap_size < min_heap_size) {
      if (min_heap_.top() < num) {
        max_heap_.push(min_heap_.top());
        min_heap_.pop();
        min_heap_.push(num);
      } else {
        max_heap_.push(num);
      }
    } else {
      if (min_heap_.empty() || min_heap_.top() < num) {
        min_heap_.push(num);
      } else {
        max_heap_.push(num);
      }
    }
  }

  double findMedian() {
    std::size_t max_heap_size = max_heap_.size();
    std::size_t min_heap_size = min_heap_.size();

    if (max_heap_size > min_heap_size) {
      return max_heap_.top();
    } else if (max_heap_size < min_heap_size) {
      return min_heap_.top();
    } else {
      return (min_heap_.top() + max_heap_.top()) / 2.0;
    }
  }

private:
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap_;
  std::priority_queue<int, std::vector<int>, std::less<int>> max_heap_;
};

int main() {
  MedianFinder median_finder;
  median_finder.addNum(1);
  std::cout << median_finder.findMedian() << std::endl;
  median_finder.addNum(2);
  std::cout << median_finder.findMedian() << std::endl;
  median_finder.addNum(3);
  std::cout << median_finder.findMedian() << std::endl;
  median_finder.addNum(4);
  std::cout << median_finder.findMedian() << std::endl;
  median_finder.addNum(5);
  std::cout << median_finder.findMedian() << std::endl;
  median_finder.addNum(6);
  std::cout << median_finder.findMedian() << std::endl;
  return 0;
}
