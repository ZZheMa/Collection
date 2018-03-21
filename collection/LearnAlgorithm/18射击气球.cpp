#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

// 452. Minimum Number of Arrows to Burst Balloons

typedef std::pair<int, int> Point;

// 贪心。
// 数形结合，用最简单的情况画出坐标图，然后进行找规律。
int findMinArrowShots(std::vector<Point>& points) {
  if (points.empty()) {
    return 0;
  }

  std::sort(points.begin(), points.end(), [](const Point& lhs, const Point& rhs) {
    return lhs.first < rhs.first;
  });

  int arrow_sum = 1;
  int right_point = points[0].second;
  for (std::size_t i = 1; i < points.size(); ++i) {
    const Point& point = points[i];

    if (right_point >= point.first) {
      if (right_point > point.second) {
        right_point = point.second;
      }
      continue;
    }

    ++arrow_sum;
    right_point = point.second;
  }

  return arrow_sum;
}

void PrintPoints(const std::vector<Point>& points) {
  for (const Point& point : points) {
    std::cout << point.first << "," << point.second << std::endl;
  }
}

void TestCase1() {
  std::vector<Point> points;
  points.push_back(std::make_pair(10, 16));
  points.push_back(std::make_pair(2, 8));
  points.push_back(std::make_pair(1, 6));
  points.push_back(std::make_pair(7, 12));

  PrintPoints(points);

  std::cout << findMinArrowShots(points) << std::endl;

  PrintPoints(points);

  std::cout << "---------------------" << std::endl;
}

void TestCase2() {
  std::vector<Point> points;
  points.push_back(std::make_pair(9,12));
  points.push_back(std::make_pair(1,10));
  points.push_back(std::make_pair(4,11));
  points.push_back(std::make_pair(8,12));
  points.push_back(std::make_pair(3,9));
  points.push_back(std::make_pair(6,9));
  points.push_back(std::make_pair(6,7));

  PrintPoints(points);

  std::cout << findMinArrowShots(points) << std::endl;

  PrintPoints(points);

  std::cout << "---------------------" << std::endl;
}

int main() {
  TestCase1();
  TestCase2();

  return 0;
}
