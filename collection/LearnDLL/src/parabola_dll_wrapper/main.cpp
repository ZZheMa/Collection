#include <iostream>
#include <string>

#include "parabola_dll_wrapper/parabola_equation_wrapper.h"

using namespace parabola_dll_wrapper;

// Given: point: (1, 2), (2, 8), (3, 18).
// Correct result: y = 2x^2.
static void Test_Case1(ParabolaEquationWrapper* wrapper) {
  wrapper->InputThreePoints(1, 2, 2, 8, 3, 18);
  if (!wrapper->IsCorrectParabola()) {
    std::cout << "Not Correct Parabola!" << std::endl;
    return;
  }

  std::cout << wrapper->GetParabolaEquationString() << std::endl;
  std::cout << wrapper->GetSlopeEquationString() << std::endl;

  double a = 0.0, b = 0.0, c = 0.0;
  wrapper->GetWeights(a, b, c);
  std::cout << "Weight: " << a << ", " << b << ", " << c << std::endl;

  std::cout << wrapper->OutputY(4) << std::endl;
  std::cout << wrapper->OutputSlope(1) << std::endl;
}

// Given: point: (0, 4), (1, 9), (2, 18).
// Correct result: y = 2x^2 + 3x + 4.
static void Test_Case2(ParabolaEquationWrapper* wrapper) {
  wrapper->InputThreePoints(0, 4, 1, 9, 2, 18);
  if (!wrapper->IsCorrectParabola()) {
    std::cout << "Not Correct Parabola!" << std::endl;
    return;
  }

  std::cout << wrapper->GetParabolaEquationString() << std::endl;
  std::cout << wrapper->GetSlopeEquationString() << std::endl;

  double a = 0.0, b = 0.0, c = 0.0;
  wrapper->GetWeights(a, b, c);
  std::cout << "Weight: " << a << ", " << b << ", " << c << std::endl;

  std::cout << wrapper->OutputY(4) << std::endl;
  std::cout << wrapper->OutputSlope(1) << std::endl;
}

// Given: point: (0, 4), (1, 7), (2, 10).
// Correct result: y = 3x + 4.
static void Test_Case3(ParabolaEquationWrapper* wrapper) {
  wrapper->InputThreePoints(0, 4, 1, 7, 2, 10);
  if (!wrapper->IsCorrectParabola()) {
    std::cout << "Not Correct Parabola!" << std::endl;
    return;
  }
}

int main() {
  ParabolaEquationWrapper* wrapper = ParabolaEquationWrapper::Instance();
  if (!wrapper->Load()) {
    return -1;
  }

  Test_Case1(wrapper);
  Test_Case2(wrapper);
  Test_Case3(wrapper);

  return 0;
}
