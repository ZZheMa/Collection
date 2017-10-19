#ifndef PARABOLA_EQUATION_SDK_THREE_ORDER_DETERMINANT_H_
#define PARABOLA_EQUATION_SDK_THREE_ORDER_DETERMINANT_H_

#include <string>

namespace parabola_equation_sdk {

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
                        double a3, double b3, double c3);

  double CalculateValue() const;

  std::string ToString() const;

private:
  double data[3][3];
};

}  // namespace parabola_equation_sdk

#endif  // PARABOLA_EQUATION_SDK_THREE_ORDER_DETERMINANT_H_
