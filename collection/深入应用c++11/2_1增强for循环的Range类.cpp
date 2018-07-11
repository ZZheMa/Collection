#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>
#include <set>

// Range左闭右开区间。通过实现Iterator使得可以使用增强for循环

// 参考《深入应用c++ 11》P40。

namespace detail_range {

template<typename T>
class Iterator {
public:
  using value_type = T;
  using size_type = std::size_t;

  Iterator(value_type initial_value, size_type cursor, value_type step)
      : initial_value_(initial_value)
      , cursor_(cursor)
      , step_(step) {
  } 

  Iterator& operator++() {  // 前置++。
    ++cursor_;
    return *this;
  }

  value_type operator*() const {
    return initial_value_ + cursor_ * step_;
  }

  bool operator!=(const Iterator& it) {
    return cursor_ != it.cursor_;
  }

private:
  value_type initial_value_;
  size_type cursor_;
  value_type step_;
};

//------------------------------------------------------------------

template<typename T>
class RangeImpl {
public:
  using value_type = T;
  using size_type = typename Iterator<value_type>::size_type;

  using iterator = Iterator<value_type>;
  using const_iterator = const Iterator<value_type>;

  using reference = value_type&;
  using const_reference = const value_type&;


  RangeImpl(value_type begin, value_type end, value_type step)
      : begin_(begin)
      , end_(end)
      , step_(step) {
    max_count_ = (end_ - begin_) / step_;
    if (static_cast<value_type>(max_count_ * step_ + begin_) < end_) {
      ++max_count_;
    }
  }

  iterator begin() {
    return{ begin_, 0, step_ };
  }

  const_iterator begin() const {
    return { begin_, 0, step_ };
  }

  iterator end() {
    return { begin_, max_count_, step_ };
  }

  const_iterator end() const {
    return { begin_, max_count_, step_ };
  }

private:
  value_type begin_;
  value_type end_;
  value_type step_;

  size_type max_count_;
};

//------------------------------------------------------------------

template<typename T>
RangeImpl<T> Range(T end) {
  return { {}, end, 1 };
}

template<typename T>
RangeImpl<T> Range(T begin, T end) {
  return { begin, end, 1 };
}

template<typename T, typename U>
auto Range(T begin ,T end, U step) -> RangeImpl<decltype(begin + step)> {
  return RangeImpl<decltype(begin + step)>(begin, end, step);
}

}

//------------------------------------------------------------------

int main() {
  auto range1 = detail_range::Range<int>(10);
  for (auto i : range1) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  auto range2 = detail_range::Range<int>(1, 4);
  for (auto i : range2) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  auto range3 = detail_range::Range<float>(1.2f, 4.5f);
  for (auto i : range3) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  auto range4 = detail_range::Range<char>('a', 'g');
  for (auto i : range4) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  auto range5 = detail_range::Range<int, float>(2, 8, 1.1);
  for (auto i : range5) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  auto range6 = detail_range::Range<int, int>(2, 8, 2);
  for (auto i : range6) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  return 0;
}
