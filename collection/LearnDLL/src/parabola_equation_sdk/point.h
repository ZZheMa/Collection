#ifndef PARABOLA_EQUATION_SDK_POINT_H_
#define PARABOLA_EQUATION_SDK_POINT_H_

#include <string>

namespace parabola_equation_sdk {

class Point {
public:
  double x;
  double y;

  Point(double x_, double y_)
      : x(x_)
      , y(y_) {
  }
};

}  // namespace parabola_equation_sdk

#endif  // PARABOLA_EQUATION_SDK_POINT_H_
