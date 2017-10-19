#ifndef PARABOLA_EQUATION_SDK_PARABOLA_EQUATION_H_
#define PARABOLA_EQUATION_SDK_PARABOLA_EQUATION_H_

#include <string>

namespace parabola_equation_sdk {

class Point;

// 一元二次方程，也就是抛物线方程: y = a·x^2 + b·x + c
// 导数方程，也就是斜率方程: y' = 2·a·x + b
class ParabolaEquation {
public:
  ParabolaEquation();

  ParabolaEquation(double a, double b, double c);

  ParabolaEquation(const Point& point1, const Point& point2, const Point& point3);

  bool is_parabola() const {
    return is_parabola_;
  }

  double a() const {
    return a_;
  }

  double b() const {
    return b_;
  }

  double c() const {
    return c_;
  }

  void InputThreePoints(const Point& point1, const Point& point2, const Point& point3);

  // 输入x, 输出对应y。
  double OutputY(double x) const;

  // 输入x, 输出对应斜率。
  double OutputSlope(double x) const;

  std::string ToParabolaEquationString() const;

  std::string ToSlopeEquationString() const;

private:
  void CalculateWeights(const Point& point1, const Point& point2, const Point& point3);

  void CheckParabolaValid();

private:
  double a_;
  double b_;
  double c_;

  bool is_parabola_;
};

}  // namespace parabola_equation_sdk

#endif  // PARABOLA_EQUATION_SDK_PARABOLA_EQUATION_H_
