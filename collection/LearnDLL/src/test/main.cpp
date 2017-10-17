#include <iostream>
#include <string>

// 1.三阶行列式
// | a1 b1 c1 |
// | a2 b2 c2 |
// | a3 b3 c3 |
 
// 2.求三阶行列式的值
// a1(b2·c3-b3·c2)-b1(a2·c3-a3·c2)+c1(a2·b3-a3·b2)

class ThreeOrderDeterminant {
public:
  ThreeOrderDeterminant(double a1, double b1, double c1,
                        double a2, double b2, double c2,
                        double a3, double b3, double c3) {
    data[0][0] = a1; data[0][1] = b1; data[0][2] = c1;
    data[1][0] = a2; data[1][1] = b2; data[1][2] = c2;
    data[2][0] = a3; data[2][1] = b3; data[2][2] = c3;
  }

  double CalculateValue() const {
    double sub_value1 = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]);
    double sub_value2 = data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]);
    double sub_value3 = data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

    double value = sub_value1 - sub_value2 + sub_value3;

    return value;
  }

  std::string ToString() const {
    std::string str;
    char buf[256] = { 0 };

    sprintf(buf, "| %-6.2lf %-6.2lf %-6.2lf |\n", data[0][0], data[0][1], data[0][2]);
    str += buf;

    sprintf(buf, "| %-6.2lf %-6.2lf %-6.2lf |\n", data[1][0], data[1][1], data[1][2]);
    str += buf;

    sprintf(buf, "| %-6.2lf %-6.2lf %-6.2lf |\n", data[2][0], data[2][1], data[2][2]);
    str += buf;

    return str;
  }

private:
  double data[3][3];
};

class Point {
public:
  double x;
  double y;

  Point(double x_, double y_)
      : x(x_)
      , y(y_) {
  }
};

// 一元二次方程，也就是抛物线方程: y = a·x^2 + b·x + c
// 导数方程，也就是斜率方程: y' = 2·a·x + b
class ParabolaEquation {
public:
  ParabolaEquation(double a, double b, double c);

  ParabolaEquation(const Point& point1, const Point& point2, const Point& point3);

  bool is_parabola() const {
    return is_parabola_;
  }

  // 输入x, 输出对应y。
  double OutputY(double x) const;

  // 输入x, 输出对应斜率。
  double OutputSlope(double x) const;

  std::string ToParabolaEquationString() const;

  std::string ToSlopeEquationString() const;

private:
  void CalculateWeights(const Point& point1, const Point& point2, const Point& point3);

private:
  double a_;
  double b_;
  double c_;

  bool is_parabola_;
};

int main() {
  ThreeOrderDeterminant s1(1, 3, 1,
                           2, 1, 1,
                           -2, 2, -1);

  std::cout << s1.CalculateValue() << std::endl;
  std::cout << s1.ToString() << std::endl;

  return 0;
}
