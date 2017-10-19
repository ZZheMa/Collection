#include "parabola_equation_dll/parabola_equation_dll.h"

#include <cassert>

#include "parabola_equation_sdk/parabola_equation.h"
#include "parabola_equation_sdk/point.h"

using namespace parabola_equation_sdk;

ParabolaEquationHandle CreateParabolaEquationHandle() {
  ParabolaEquationHandle handle = new ParabolaEquation();

  return handle;
}

void InputThreePoints(ParabolaEquationHandle* handle,
                      double x1,
                      double y1,
                      double x2,
                      double y2,
                      double x3,
                      double y3) {
  assert(handle != NULL);

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  parabola->InputThreePoints(Point(x1, y1), Point(x2, y2), Point(x3, y3));
}