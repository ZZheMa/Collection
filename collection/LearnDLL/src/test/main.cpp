#include <iostream>
#include <sstream>
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

static const std::string kError = "The equation is wrong!";

// 一元二次方程，也就是抛物线方程: y = a·x^2 + b·x + c
// 导数方程，也就是斜率方程: y' = 2·a·x + b
class ParabolaEquation {
public:
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

  // 输入x, 输出对应y。
  double OutputY(double x) const;

  // 输入x, 输出对应斜率。
  double OutputSlope(double x) const;

  std::string ToParabolaEquationString() const;

  std::string ToSlopeEquationString() const;

private:
  ParabolaEquation();

  void CalculateWeights(const Point& point1, const Point& point2, const Point& point3);

  void CheckParabolaValid();

private:
  double a_;
  double b_;
  double c_;

  bool is_parabola_;
};

ParabolaEquation::ParabolaEquation(double a, double b, double c)
    : a_(a)
    , b_(b)
    , c_(c)
    , is_parabola_(true) {
  CheckParabolaValid();
}

ParabolaEquation::ParabolaEquation(const Point& point1, const Point& point2, const Point& point3)
    : is_parabola_(true) {
  CalculateWeights(point1, point2, point3);
}

// Given point1(x1, y1), point2(x2, y2), point3(x3, y3),
// we can get three equations.
// y1 = a·x1^2 + b·x1 + c
// y2 = a·x2^2 + b·x2 + c
// y3 = a·x3^2 + b·x3 + c
// And then we can use Cramer's rule to calculate the weights a, b, c.
void ParabolaEquation::CalculateWeights(const Point& point1, const Point& point2, const Point& point3) {
  double x1 = point1.x, x2 = point2.x, x3 = point3.x;
  double y1 = point1.y, y2 = point2.y, y3 = point3.y;

  double x1_2 = x1 * x1, x2_2 = x2 * x2, x3_2 = x3 * x3;

  ThreeOrderDeterminant D(x1_2, x1, 1,
                          x2_2, x2, 1,
                          x3_2, x3, 1);

  double d = D.CalculateValue();
  if (d == 0) {
    is_parabola_ = false;
    return;
  }

  ThreeOrderDeterminant Da(y1, x1, 1,
                           y2, x2, 1,
                           y3, x3, 1);
  double da = Da.CalculateValue();
  if (da == 0) {
    is_parabola_ = false;
    return;
  }

  a_ = da / d;

  ThreeOrderDeterminant Db(x1_2, y1, 1,
                           x2_2, y2, 1,
                           x3_2, y3, 1);
  b_ = Db.CalculateValue() / d;

  ThreeOrderDeterminant Dc(x1_2, x1, y1,
                           x2_2, x2, y2,
                           x3_2, x3, y3);
  c_ = Dc.CalculateValue() / d;
}

void ParabolaEquation::CheckParabolaValid() {
  is_parabola_ = (a_ != 0);
}

double ParabolaEquation::OutputY(double x) const {
  if (!is_parabola_) {
    return 0.0;
  }

  double y = a_ * x * x + b_ * x + c_;
  return y;
}

double ParabolaEquation::OutputSlope(double x) const {
  if (!is_parabola_) {
    return 0.0;
  }

  double y = 2 * a_ * x + b_;
  return y;
}

std::string ParabolaEquation::ToParabolaEquationString() const {
  if (!is_parabola_) {
    return kError;
  }

  std::ostringstream sstr;
  sstr << "y = " << a_ << "x^2";

  if (b_ != 0) {
    sstr << " + " << b_ << "x";
  }

  if (c_ != 0) {
    sstr << " + " << c_;
  }

  return sstr.str();
}

std::string ParabolaEquation::ToSlopeEquationString() const {
  if (!is_parabola_) {
    return kError;
  }

  double a = a_ * 2;

  std::ostringstream sstr;
  sstr << "y = " << a << "x";

  if (b_ != 0) {
    sstr << " + " << b_;
  }

  return sstr.str();
}

int main() {
  //ThreeOrderDeterminant s1(1, 3, 1,
  //                         2, 1, 1,
  //                         -2, 2, -1);

  //std::cout << s1.CalculateValue() << std::endl;
  //std::cout << s1.ToString() << std::endl;

  ParabolaEquation equation1(Point(0, 1.1), Point(1, 6), Point(2, 17));
  if (equation1.is_parabola()) {
    std::cout << equation1.ToParabolaEquationString() << std::endl;
    std::cout << equation1.ToSlopeEquationString() << std::endl;
  }

  ParabolaEquation equation2(Point(1, 6), Point(2, 24), Point(3, 54));
  if (equation2.is_parabola()) {
    std::cout << equation2.ToParabolaEquationString() << std::endl;
    std::cout << equation2.ToSlopeEquationString() << std::endl;
  }

  return 0;
}
