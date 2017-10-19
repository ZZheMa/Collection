#include "parabola_equation_sdk/parabola_equation.h"

#include <sstream>

#include "parabola_equation_sdk/point.h"
#include "parabola_equation_sdk/three_order_determinant.h"

namespace parabola_equation_sdk {

static const std::string kError = "The equation is wrong!";

ParabolaEquation::ParabolaEquation()
    : a_(0.0)
    , b_(0.0)
    , c_(0.0)
    , is_parabola_(false) {
}

ParabolaEquation::ParabolaEquation(double a, double b, double c)
    : a_(a)
    , b_(b)
    , c_(c)
    , is_parabola_(false) {
  CheckParabolaValid();
}

void ParabolaEquation::InputThreePoints(const Point& point1, const Point& point2, const Point& point3) {
  CalculateWeights(point1, point2, point3);
}

ParabolaEquation::ParabolaEquation(const Point& point1, const Point& point2, const Point& point3)
    : is_parabola_(false) {
  CalculateWeights(point1, point2, point3);
}

// Given point1(x1, y1), point2(x2, y2), point3(x3, y3),
// we can get three equations.
// y1 = a，x1^2 + b，x1 + c
// y2 = a，x2^2 + b，x2 + c
// y3 = a，x3^2 + b，x3 + c
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

  is_parabola_ = true;
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


}  // namespace parabola_equation_sdk
