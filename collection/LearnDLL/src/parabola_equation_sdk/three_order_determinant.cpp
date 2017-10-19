#include "parabola_equation_sdk/three_order_determinant.h"

namespace parabola_equation_sdk {

ThreeOrderDeterminant::ThreeOrderDeterminant(double a1, double b1, double c1,
                                             double a2, double b2, double c2,
                                             double a3, double b3, double c3) {
    data[0][0] = a1; data[0][1] = b1; data[0][2] = c1;
    data[1][0] = a2; data[1][1] = b2; data[1][2] = c2;
    data[2][0] = a3; data[2][1] = b3; data[2][2] = c3;
  }

double ThreeOrderDeterminant::CalculateValue() const {
  double sub_value1 = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]);
  double sub_value2 = data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]);
  double sub_value3 = data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

  double value = sub_value1 - sub_value2 + sub_value3;

  return value;
}

std::string ThreeOrderDeterminant::ToString() const {
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

}  // namespace parabola_equation_sdk
